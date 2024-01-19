from msilib.schema import IsolatedComponent
from idc import BADADDR, INF_BASEADDR, SEARCH_DOWN, FUNCATTR_START, FUNCATTR_END
import idc
import idaapi
import datetime
import re

ADDRESSES_DIR               = "C:\\Users\\zakuraai\\Chimera\\Chimera.Core\\Core\\leaguescript\\Addresses\\Addresses.h"
FileR3dRenderer             = "C:\\Users\\zakuraai\\Chimera\\Chimera.Core\\Core\\leaguescript\\Framework\\Rendering\\r3dRenderer\\r3dRenderer.cpp"
FileGameObject              = "C:\\Users\\zakuraai\\Chimera\\Chimera.Core\\Core\\leaguescript\\Framework\\GameObjects\\GameObject\\GameObject.cpp"
FileSpellbook               = "C:\\Users\\zakuraai\\Chimera\\Chimera.Core\\Core\\leaguescript\\Framework\\Spells\\Spellbook\\Spellbook.cpp"
FileEventSystem             = "C:\\Users\\zakuraai\\Chimera\\Chimera.Core\\Core\\leaguescript\\Framework\\GameEngine\\EventSystem\\EventSystem.cpp"

def GetHookBytesFromFile(filepath, keyword):
    try:
        with open(filepath, 'r') as file:
            for line in file:
                if keyword in line:
                    # Find the index of the substring 'Callee, ' within the line
                    index_callee = line.find('Callee, ')
                    if index_callee != -1:
                        # Extract the number and remove the last 2 characters
                        number = line[index_callee + 8:-3]
                        return number.rstrip()  # Return as a string
        # If the keyword is not found in any line
        return None
    except FileNotFoundError:
        print(f"File '{filepath}' not found.")
        return None

def GetOffsetAndSig(keyword):
    file_path = ADDRESSES_DIR
    result_pairs = []
    with open(file_path, 'r') as file:
        for line in file:
            # Use regular expression to find exact word match for the keyword
            pattern = r'\b' + re.escape(keyword) + r'\b'
            if re.search(pattern, line):
                # Split the line at '=' and take the value after '='
                parts = line.split('=')
                if len(parts) == 2:
                    value = parts[1].split(',')[0].strip()

                    # Find the "SIG:" substring and take the value after it
                    sig_index = line.find("SIG:")
                    if sig_index != -1:
                        sig_end_index = line.find("//", sig_index)
                        if sig_end_index != -1:
                            sig_value = line[sig_index + 4:sig_end_index].strip()
                        else:
                            sig_value = line[sig_index + 4:].strip()
                    else:
                        sig_value = ""

                    # Append the pair of values to the result list
                    result_pairs.append((value, sig_value))

    return result_pairs

def ReplaceValue(keyword_to_replace, new_value):
    result_pairs = GetOffsetAndSig(keyword_to_replace)

    # Iterate through the list of pairs and replace the value in each line
    with open(ADDRESSES_DIR, 'r') as file:
        lines = file.readlines()

    for value, sig_value in result_pairs:
        for i, line in enumerate(lines):
            # Use regular expression to find exact word match for the keyword to replace
            pattern = r'\b' + re.escape(keyword_to_replace) + r'\b'
            if re.search(pattern, line):
                # Replace the old value with the new value
                lines[i] = line.replace(value, new_value)

    # Write the modified lines back to the file
    with open(ADDRESSES_DIR, 'w') as file:
        file.writelines(lines)

def DecToHex(Addr):
	return "0%0.2X" % Addr
    
def DecToHexString(Addr):
	return "0x%0.2X" % Addr

def MakeEnum(enumName, offsetArray):
    print ("enum class %s : unsigned int\r\n{" % enumName)
    for offset in offsetArray:        
        if len(offset[0]) == 0:
            print ("")
            continue
        if type(offset[1]) is str:
            print ("   %s = %s," % ( offset[0], offset[1]))
            continue

        fncValue = offset[1] if offset[1] != -1 else 0x0

        tempName = enumName + offset[0] if offset[0] == "Instance" else offset[0]

        locByName = idc.get_name_ea_simple(tempName)
        isMismatch = locByName == 0x0

        if locByName == BADADDR:
            locByName = fncValue
        
        if locByName > idaapi.get_imagebase():
            set_name(locByName, tempName)
            locByName = locByName - idaapi.get_imagebase()

        isSame = DecToHexString(locByName) == offset[2][0][0]
        #print("%s | %s | %s" % (locByName, DecToHexString(locByName), offset[2][0][0]))

        print ("   %s = %s, %s %s" % (offset[0], DecToHexString(locByName), '// Possible mismatch' if isMismatch else '', "// same" if isSame else ''))

    print ("};\r\n")
    
def MakeEnumHook(enum_name, enum_values):
    print(f"enum class {enum_name} {{")

    for name, value, old in enum_values:
        isSame = str(old) == str(value)
        comment = "// same" if isSame else ''
        print(f"    {name} = {value}, {comment}")

    print("};\n")
    
def FindFunctionAddr(name, offset, operandValue):
    address = idc.find_binary(0, SEARCH_DOWN, "\"" + name + "\"")
    dword = -1
    
    if address == BADADDR:
        return BADADDR
    
    xrefs = XrefsTo(address)
    for xref in xrefs:
        dword = xref.frm + offset
    
    if dword == BADADDR:
        return BADADDR
    
    return idc.get_operand_value(dword, operandValue)

def FindOffsetPattern(Pattern, Operand, Offset=0):
    addr = idc.find_binary(0, SEARCH_DOWN, Pattern[0][1])
    
    if addr == BADADDR: return 0

    newAddr = addr + Offset;
    
    return idc.get_operand_value(newAddr, Operand)
    
def FindFunctionFirstXRef(name):
    address = idc.find_binary(0, SEARCH_DOWN, "\"" + name + "\"")
    dword = BADADDR
    
    if address == BADADDR:
        return BADADDR
    
    xrefs = XrefsTo(address)
    for xref in xrefs:
        dword = xref.frm
    
    try:
        return idaapi.get_func(dword).start_ea
    except Exception:
        return -1

def FindFunctionStart(pattern):
    address = idc.find_binary(0, SEARCH_DOWN, pattern[0][1])
    if address == BADADDR:
        return BADADDR
    

    try:
        return idaapi.get_func(address).start_ea
    except Exception:
        return -1
        
def FindFunctionCall(Pattern):
    addr = idc.find_binary(0, SEARCH_DOWN, Pattern[0][1])

    if addr == BADADDR: return 0

    return idc.get_operand_value(addr, 0)
    
def FindBytesForHook(FunctionStart):
    cntBytes = 0
    
    while (cntBytes < 14):
        #print ("%s : %s" % (FunctionStart + cntBytes, idc.get_bytes(FunctionStart + cntBytes, idc.get_item_size(FunctionStart + cntBytes))))
        cntBytes += len(idc.get_bytes(FunctionStart + cntBytes, idc.get_item_size(FunctionStart + cntBytes)))
        
    return cntBytes

def PrintClassSizeChange(ClassName, Pattern, LastPatchSize):

    LastPatchSize = DecToHexString(LastPatchSize)
    addr = idc.find_binary(0, SEARCH_DOWN, Pattern)
    if addr == BADADDR: return 0
    newAddr = addr - 0x19
    classSize = DecToHexString(idc.get_operand_value(newAddr, 1))

    if classSize == LastPatchSize:
        print(ClassName + ": OK (" + classSize + ")")
    else:
        diff = DecToHexString(int(classSize, 0) - int(LastPatchSize, 0))
        print(ClassName + ": !NOK! (" + diff + ") (" + classSize + ")")

def main():

    print ("------------------------------------")
    print ("*** STARTING TO MATCH CLASS SIZES ***")
    print ("------------------------------------")
    PrintClassSizeChange("GameObject", "64 8B AC 1F", 0x290)
    PrintClassSizeChange("AIHeroClient", "2C 30 60 E2", 0x4CA8)
    PrintClassSizeChange("MissileClient", "94 DE 8A 9C", 0x528)

    print ("------------------------------------")
    print ("*** STARTING TO GET ADDRESSES FROM HEADER ***")
    print ("------------------------------------")

    # Bypass
    CastSpellFlag               = GetOffsetAndSig("CastSpellFlag")
    IssueOrderFlag              = GetOffsetAndSig("IssueOrderFlag")
    DetectionWatcher            = GetOffsetAndSig("DetectionWatcher")
    
    # r3dRenderer
    r3dRendererInstance         = GetOffsetAndSig("r3dRendererInstance")
    screenInstance              = GetOffsetAndSig("screenInstance")
    WorldToScreen               = GetOffsetAndSig("WorldToScreen")
    ViewProjectionMatrix        = GetOffsetAndSig("ViewProjectionMatrix")
    RenderUsualSuspects         = GetOffsetAndSig("RenderUsualSuspects")
    RenderMouseOvers            = GetOffsetAndSig("RenderMouseOvers")
    LoadTexture                 = GetOffsetAndSig("LoadTexture")
    LoadTextureFirstArg         = GetOffsetAndSig("LoadTextureFirstArg")
    ZoomCheatDetectionFlag      = GetOffsetAndSig("ZoomCheatDetectionFlag")
    RenderEffect                = GetOffsetAndSig("RenderEffect")
    
    # ObjectManager
    ObjectManagerInstance       = GetOffsetAndSig("ObjectManagerInstance")
    GetFirstObject              = GetOffsetAndSig("GetFirstObject")
    GetNextObject               = GetOffsetAndSig("GetNextObject")
    FindObject                  = GetOffsetAndSig("FindObject")
    GetNetworkObject            = GetOffsetAndSig("GetNetworkObject")
    
    # GameObjectAddresses
    OnCreateObject              = GetOffsetAndSig("OnCreateObject")
    OnDeleteObject              = GetOffsetAndSig("OnDeleteObject")
    OnCastComplete              = GetOffsetAndSig("OnCastComplete")
    OnProcessSpell              = GetOffsetAndSig("OnProcessSpell")
    OnStopCast                  = GetOffsetAndSig("OnStopCast")
    SetPath                     = GetOffsetAndSig("SetPath")
    OnBuffAdd                   = GetOffsetAndSig("OnBuffAdd")
    OnBuffRemove                = GetOffsetAndSig("OnBuffRemove")
    PlayAnimation               = GetOffsetAndSig("PlayAnimation")
    ProcessAutoAttack           = GetOffsetAndSig("ProcessAutoAttack")
    GetAttackDelay              = GetOffsetAndSig("GetAttackDelay")
    GetAttackCastDelay          = GetOffsetAndSig("GetAttackCastDelay")
    GetBasicAttack              = GetOffsetAndSig("GetBasicAttack")
    CompareTypeFlags            = GetOffsetAndSig("CompareTypeFlags")
    GetHealthBarScreenPosition  = GetOffsetAndSig("GetHealthBarScreenPosition")
    BaseDrawPosition            = GetOffsetAndSig("BaseDrawPosition")
    GetOwnerPlayer              = GetOffsetAndSig("GetOwnerPlayer")
    GetBaseHealthForLevel       = GetOffsetAndSig("GetBaseHealthForLevel")
    IsAlive                     = GetOffsetAndSig("IsAlive")
    IsDead                      = GetOffsetAndSig("IsDead")
    IsClone                     = GetOffsetAndSig("IsClone")
    UpdateCharacterDataStack    = GetOffsetAndSig("UpdateCharacterDataStack")
    PushCharacterDataStack      = GetOffsetAndSig("PushCharacterDataStack")
    GetCircleIconPortrait       = GetOffsetAndSig("GetCircleIconPortrait")
    GetSquareIconPortrait       = GetOffsetAndSig("GetSquareIconPortrait")
    GetTotalRespawnTime         = GetOffsetAndSig("GetTotalRespawnTime")
    GetRespawnTimeRemaining     = GetOffsetAndSig("GetRespawnTimeRemaining")
    GetTimerExpiry              = GetOffsetAndSig("GetTimerExpiry")
    GetGoldGivenOnDeath         = GetOffsetAndSig("GetGoldGivenOnDeath")
    SpellslotCanBeUpgraded      = GetOffsetAndSig("SpellslotCanBeUpgraded")
    BuyItem                     = GetOffsetAndSig("BuyItem")
    CreateClientEffect          = GetOffsetAndSig("CreateClientEffect")
    
    # BuffEntry
    BuffEntryIsValid            = GetOffsetAndSig("LITERAL: BuffEntry_IsValid")
    
    # GameClient
    GameClientInstance          = GetOffsetAndSig("GameClientInstance")

    # GameStartData
    GameStartDataInstance       = GetOffsetAndSig("GameStartDataInstance")
    GetMissionMode              = GetOffsetAndSig("GetMissionMode")
    GetMapID                    = GetOffsetAndSig("GetMapID")
    GetRegion                   = GetOffsetAndSig("GetRegion")
    GetGameID                   = GetOffsetAndSig("GetGameID")

    # ManagerList
    M_MinionList                = GetOffsetAndSig("M_MinionList")
    M_HeroList                  = GetOffsetAndSig("M_HeroList")
    M_TurretList                = GetOffsetAndSig("M_TurretList")
    M_MissileList               = GetOffsetAndSig("M_MissileList")
    
    # SpellDataInst
    GetIconTexture              = GetOffsetAndSig("GetIconTexture") 
    
    # LocalPlayer
    LocalPlayerInstance         = GetOffsetAndSig("LocalPlayerInstance")  
    IssueOrder                  = GetOffsetAndSig("IssueOrder")  
    
    # Spellbook
    SendSpellcastPacket         = GetOffsetAndSig("SendSpellcastPacket")  
    UpdateChargedSpell          = GetOffsetAndSig("UpdateChargedSpell")  
    OnSpellImpact               = GetOffsetAndSig("OnSpellImpact")  
    GetSpellState               = GetOffsetAndSig("GetSpellState")  
    OnDoCast                    = GetOffsetAndSig("OnDoCast")  

    # EventSystem
    Notify                      = GetOffsetAndSig("Notify")
    ConvertEventToName          = GetOffsetAndSig("ConvertEventToName")
    
    # Game
    GameVersion                 = GetOffsetAndSig("GameVersion")  
    OnMainLoop                  = GetOffsetAndSig("OnMainLoop")  
    OnWorldDraw                 = GetOffsetAndSig("OnWorldDraw")  
    OnHUDDraw                   = GetOffsetAndSig("OnHUDDraw")  
    GameTime                    = GetOffsetAndSig("GameTime")  
    HandleConfirmQuitGame       = GetOffsetAndSig("HandleConfirmQuitGame")
    
    # NetClient
    NetClientInstance           = GetOffsetAndSig("LITERAL: NetClientInstance")  
    GetNetClientInstance        = GetOffsetAndSig("GetNetClientInstance")  
    GetPing                     = GetOffsetAndSig("GetPing")  
    
    # Minimap
    MinimapInstance             = GetOffsetAndSig("MinimapInstance")      
    
    # Zoom
    ZoomInstance                = GetOffsetAndSig("LITERAL: ZoomInstance")      
    
    # Chat
    ChatInstance                = GetOffsetAndSig("ChatInstance")     
    ChatClient                  = GetOffsetAndSig("ChatClient")     
    MenuGui                     = GetOffsetAndSig("MenuGui")     
    PrintChat                   = GetOffsetAndSig("PrintChat")     
    SendChat                    = GetOffsetAndSig("SendChat")     
    
    # Hud
    HudInstance                 = GetOffsetAndSig("HudInstance") 
    
    # NavMesh
    NavMeshInstance             = GetOffsetAndSig("NavMeshInstance")     
    IsNotWall                   = GetOffsetAndSig("IsNotWall")     
    GetCellHeight               = GetOffsetAndSig("GetCellHeight")     
    GetCellFlags                = GetOffsetAndSig("GetCellFlags")     
    AssignNavCellStateFlags     = GetOffsetAndSig("AssignNavCellStateFlags")     
    GetCellLocator              = GetOffsetAndSig("GetCellLocator")     
    GetCellSize                 = GetOffsetAndSig("GetCellSize")     
    GetCellCenter                 = GetOffsetAndSig("GetCellCenter")     
    IsInFOW                     = GetOffsetAndSig("IsInFOW")     
    
    # PathControllerCommon
    BuildNavigationPath         = GetOffsetAndSig("BuildNavigationPath")   
    CreatePath                  = GetOffsetAndSig("CreatePath")   
    SmoothPath                  = GetOffsetAndSig("SmoothPath")   
    
    HookOnGameTick              = GetHookBytesFromFile(FileR3dRenderer, "HookOnGameTick")
    HookDrawEnvironment         = GetHookBytesFromFile(FileR3dRenderer, "HookDrawEnvironment")
    HookOnRenderMouseOvers      = GetHookBytesFromFile(FileR3dRenderer, "HookOnRenderMouseOvers")
    HookHandleConfirmQuitGame   = GetHookBytesFromFile(FileR3dRenderer, "HookHandleConfirmQuitGame")
    
    HookOnProcessSpell          = GetHookBytesFromFile(FileGameObject, "HookOnProcessSpell")
    HookOnCreateObject          = GetHookBytesFromFile(FileGameObject, "HookOnCreateObject")
    HookOnDeleteObject          = GetHookBytesFromFile(FileGameObject, "HookOnDeleteObject")
    HookOnIssueOrder            = GetHookBytesFromFile(FileGameObject, "HookOnIssueOrder")
    HookOnPlayAnimation         = GetHookBytesFromFile(FileGameObject, "HookOnPlayAnimation")
    HookOnBuffAdd               = GetHookBytesFromFile(FileGameObject, "HookOnBuffAdd")
    HookOnBuffRemove            = GetHookBytesFromFile(FileGameObject, "HookOnBuffRemove")
    HookOnProcessAutoAttack     = GetHookBytesFromFile(FileGameObject, "HookOnProcessAutoAttack")

    
    HookOnCastspell             = GetHookBytesFromFile(FileSpellbook, "HookOnCastspell")
    HookOnStopCast              = GetHookBytesFromFile(FileSpellbook, "HookOnStopCast")
    HookOnCastComplete          = GetHookBytesFromFile(FileSpellbook, "HookOnCastComplete")
    HookOnSpellImpact           = GetHookBytesFromFile(FileSpellbook, "HookOnSpellImpact")

    HookOnNotify                = GetHookBytesFromFile(FileEventSystem, "HookOnNotify")

    print ("------------------------------------")
    print ("*** STARTING TO MATCH SIGNATURES ***")
    print ("------------------------------------")

    MakeEnum("Bypass", [
        ["CastSpellFlag",                   FindOffsetPattern(CastSpellFlag, 0, 5),                 CastSpellFlag],
        ["IssueOrderFlag",                  FindOffsetPattern(IssueOrderFlag, 0, 5),                IssueOrderFlag],
        ["DetectionWatcher",                FindOffsetPattern(DetectionWatcher, 1),                 DetectionWatcher],
    ])

    MakeEnum("r3dRenderer", [
        ["r3dRendererInstance",             FindOffsetPattern(r3dRendererInstance, 0, 7),           r3dRendererInstance],
        ["screenInstance",                  FindOffsetPattern(screenInstance, 1),                   screenInstance],
        ["WorldToScreen",                   FindFunctionStart(WorldToScreen),                       WorldToScreen],
        ["ViewProjectionMatrix",            FindOffsetPattern(ViewProjectionMatrix, 1),             ViewProjectionMatrix],
        ["RenderUsualSuspects",             FindFunctionCall(RenderUsualSuspects),                  RenderUsualSuspects],
        ["RenderMouseOvers",                FindFunctionCall(RenderMouseOvers),                    RenderMouseOvers],
        ["LoadTexture",                     FindFunctionCall(LoadTexture),                          LoadTexture],
        ["LoadTextureFirstArg",             FindOffsetPattern(LoadTextureFirstArg, 1),              LoadTextureFirstArg],
        ["ZoomCheatDetectionFlag",          FindOffsetPattern(ZoomCheatDetectionFlag, 0, 11),       ZoomCheatDetectionFlag],
        ["RenderEffect",                    FindFunctionStart(RenderEffect),                        RenderEffect]
    ])
    
    MakeEnum("ObjectManager", [
        ["ObjectManagerInstance",           FindOffsetPattern(ObjectManagerInstance, 1),            ObjectManagerInstance],
        ["GetFirstObject",                  FindFunctionCall(GetFirstObject),                       GetFirstObject],
        ["GetNextObject",                   FindFunctionStart(GetNextObject),                       GetNextObject],
        ["FindObject",                      FindFunctionCall(FindObject),                           FindObject],
        ["GetNetworkObject",                FindFunctionCall(GetNetworkObject),                     GetNetworkObject],
    ])

    MakeEnum("GameObjectAddresses", [
        ["OnCreateObject",                  FindFunctionCall(OnCreateObject),                       OnCreateObject],
        ["OnDeleteObject",                  FindFunctionCall(OnDeleteObject),                       OnDeleteObject],
        ["OnCastComplete",                  FindFunctionStart(OnCastComplete),                      OnCastComplete],
        ["OnProcessSpell",                  FindFunctionStart(OnProcessSpell),                      OnProcessSpell],
        ["OnStopCast",                      FindFunctionStart(OnStopCast),                          OnStopCast],
        ["SetPath",                         FindFunctionCall(SetPath),                              SetPath],
        ["OnBuffAdd",                       FindFunctionCall(OnBuffAdd),                            OnBuffAdd],
        ["OnBuffRemove",                    FindFunctionStart(OnBuffRemove),                        OnBuffRemove],
        ["PlayAnimation",                   FindFunctionStart(PlayAnimation),                       PlayAnimation],
        ["ProcessAutoAttack",               FindFunctionCall(ProcessAutoAttack),                   ProcessAutoAttack],
        ["GetAttackDelay",                  FindFunctionStart(GetAttackDelay),                      GetAttackDelay],
        ["GetAttackCastDelay",              FindFunctionCall(GetAttackCastDelay),                   GetAttackCastDelay],
        ["GetBasicAttack",                  FindFunctionCall(GetBasicAttack),                       GetBasicAttack],
        ["CompareTypeFlags",                FindFunctionStart(CompareTypeFlags),                    CompareTypeFlags],
        ["GetHealthBarScreenPosition",      FindFunctionCall(GetHealthBarScreenPosition),           GetHealthBarScreenPosition],
        ["BaseDrawPosition",                FindFunctionCall(BaseDrawPosition),                     BaseDrawPosition],
        ["GetOwnerPlayer",                  FindFunctionCall(GetOwnerPlayer),                      GetOwnerPlayer],
        ["GetBaseHealthForLevel",           FindFunctionCall(GetBaseHealthForLevel),                GetBaseHealthForLevel],
        ["IsAlive",                         FindFunctionCall(IsAlive),                              IsAlive],
        ["IsDead",                          FindFunctionCall(IsDead),                               IsDead],
        ["IsClone",                         FindFunctionStart(IsClone),                             IsClone],
        ["UpdateCharacterDataStack",        FindFunctionCall(UpdateCharacterDataStack),             UpdateCharacterDataStack],
        ["PushCharacterDataStack",          FindFunctionCall(PushCharacterDataStack),               PushCharacterDataStack],
        ["GetCircleIconPortrait",           FindFunctionCall(GetCircleIconPortrait),                GetCircleIconPortrait],
        ["GetSquareIconPortrait",           FindFunctionCall(GetSquareIconPortrait),                GetSquareIconPortrait],
        ["GetTotalRespawnTime",             FindFunctionStart(GetTotalRespawnTime),                 GetTotalRespawnTime],
        ["GetRespawnTimeRemaining",         FindFunctionStart(GetRespawnTimeRemaining),             GetRespawnTimeRemaining],
        ["GetTimerExpiry",                  FindFunctionStart(GetTimerExpiry),                       GetTimerExpiry],
        ["GetGoldGivenOnDeath",             FindFunctionStart(GetGoldGivenOnDeath),                 GetGoldGivenOnDeath],
        ["SpellslotCanBeUpgraded",          FindFunctionCall(SpellslotCanBeUpgraded),               SpellslotCanBeUpgraded],
        ["BuyItem",                         FindFunctionStart(BuyItem),                             BuyItem],
        ["CreateClientEffect",              FindFunctionCall(CreateClientEffect),                   CreateClientEffect],
    ])
    
    MakeEnum("GameClient", [
        ["GameClientInstance",              FindOffsetPattern(GameClientInstance, 1),               GameClientInstance]
    ])

    MakeEnum("GameStartData", [
        ["GameStartDataInstance",           FindOffsetPattern(GameStartDataInstance, 1),            GameStartDataInstance],
        ["GetMissionMode",                  FindFunctionCall(GetMissionMode),                       GetMissionMode],
        ["GetMapID",                        FindFunctionCall(GetMapID),                             GetMapID],
        ["GetRegion",                       FindFunctionCall(GetRegion),                            GetRegion],
        ["GetGameID",                       FindFunctionCall(GetGameID),                            GetGameID]
    ])

    MakeEnum("BuffEntry", [
        ["IsValid",                         FindFunctionCall(BuffEntryIsValid),                     BuffEntryIsValid]
    ])

    MakeEnum("ManagerList", [
        ["M_MinionList",                    FindOffsetPattern(M_MinionList, 1),                     M_MinionList],
        ["M_HeroList",                      FindOffsetPattern(M_HeroList, 1),                       M_HeroList],
        ["M_TurretList",                    FindOffsetPattern(M_TurretList, 1),                     M_TurretList],
        ["M_MissileList",                   FindOffsetPattern(M_MissileList, 1),                    M_MissileList]
    ])
    
    MakeEnum("SpellDataInst", [
        ["GetIconTexture",                  FindFunctionStart(GetIconTexture),                      GetIconTexture]
    ])

    MakeEnum("LocalPlayer", [
        ["LocalPlayerInstance",             FindOffsetPattern(LocalPlayerInstance, 1),              LocalPlayerInstance],
        ["IssueOrder",                      FindFunctionCall(IssueOrder),                           IssueOrder]
    ])

    MakeEnum("Spellbook", [
        ["SendSpellcastPacket",             FindFunctionCall(SendSpellcastPacket),                  SendSpellcastPacket],
        ["UpdateChargedSpell",              FindFunctionCall(UpdateChargedSpell),                   UpdateChargedSpell],
        ["OnSpellImpact",                   FindFunctionStart(OnSpellImpact),                       OnSpellImpact],
        ["GetSpellState",                   FindFunctionCall(GetSpellState),                        GetSpellState],
        ["OnDoCast",                        FindFunctionStart(OnDoCast),                            OnDoCast],
    ])

    MakeEnum("EventSystem", [
        ["Notify",                          FindFunctionCall(Notify),                              Notify],
        ["ConvertEventToName",              FindFunctionStart(ConvertEventToName),                  ConvertEventToName],
    ])

    MakeEnum("Game", [
        ["GameVersion",                     FindFunctionCall(GameVersion),                          GameVersion],
        ["OnMainLoop",                      FindFunctionCall(OnMainLoop),                           OnMainLoop],
        ["OnWorldDraw",                     FindFunctionCall(OnWorldDraw),                          OnWorldDraw],
        ["OnHUDDraw",                       FindFunctionCall(OnHUDDraw),                            OnHUDDraw],
        ["GameTime",                        FindOffsetPattern(GameTime, 1),                         GameTime],
        ["HandleConfirmQuitGame",           FindFunctionCall(HandleConfirmQuitGame),                HandleConfirmQuitGame],
    ])

    MakeEnum("NetClient", [
        ["Instance",                        FindOffsetPattern(NetClientInstance, 1),                NetClientInstance],
        ["GetNetClientInstance",            FindFunctionCall(GetNetClientInstance),                 GetNetClientInstance],
        ["GetPing",                         FindFunctionCall(GetPing),                              GetPing],
    ])
    
    MakeEnum("Minimap", [
        ["MinimapInstance",                 FindOffsetPattern(MinimapInstance, 1, 4),               MinimapInstance],
    ])

    MakeEnum("Zoom", [
        ["Instance",                        FindOffsetPattern(ZoomInstance, 0, 4),                  ZoomInstance],
    ])

    MakeEnum("Chat", [
        ["ChatInstance",                    FindOffsetPattern(ChatInstance, 1, 2),                  ChatInstance],
        ["ChatClient",                      FindOffsetPattern(ChatClient, 1, 3),                    ChatClient],
        ["MenuGui",                         FindOffsetPattern(MenuGui, 1),                          MenuGui],
        ["PrintChat",                       FindFunctionCall(PrintChat),                            PrintChat],
        ["SendChat",                        FindFunctionStart(SendChat),                            SendChat]
    ])

    MakeEnum("Hud", [
        ["HudInstance",                     FindOffsetPattern(HudInstance, 1, 4),                   HudInstance],
    ])

    MakeEnum("NavGrid", [
        ["NavMeshInstance",                 FindOffsetPattern(NavMeshInstance, 0),                  NavMeshInstance],
        ["IsNotWall",                       FindFunctionCall(IsNotWall),                            IsNotWall],
        ["GetCellHeight",                   FindFunctionCall(GetCellHeight),                        GetCellHeight],
        ["GetCellFlags",                    FindFunctionCall(GetCellFlags),                         GetCellFlags],
        ["AssignNavCellStateFlags",         FindFunctionCall(AssignNavCellStateFlags),              AssignNavCellStateFlags], 
        ["GetCellLocator",                  FindFunctionCall(GetCellLocator),                       GetCellLocator],
        ["GetCellSize",                     FindFunctionCall(GetCellSize),                          GetCellSize],
        ["GetCellCenter",                   FindFunctionCall(GetCellCenter),                          GetCellCenter],
        ["IsInFOW",                         FindFunctionCall(IsInFOW),                             IsInFOW]
    ])

    MakeEnum("PathControllerCommon", [
        ["BuildNavigationPath",             FindFunctionCall(BuildNavigationPath),                  BuildNavigationPath],
        ["CreatePath",                      FindFunctionCall(CreatePath),                           CreatePath],
        ["SmoothPath",                      FindFunctionStart(SmoothPath),                          SmoothPath],
    ])
    
    print ("------------------------------------")
    print ("*** STARTING TO MATCH HOOKS ***")
    print ("------------------------------------")
    
    MakeEnumHook("r3dRenderer", [
        ["HookOnGameTick",                  FindBytesForHook(FindFunctionCall(OnMainLoop)),             HookOnGameTick],
        ["HookDrawEnvironment",             FindBytesForHook(FindFunctionCall(OnWorldDraw)),            HookDrawEnvironment],
        ["HookOnRenderMouseOvers",          FindBytesForHook(FindFunctionCall(RenderMouseOvers)),       HookOnRenderMouseOvers],
        ["HookHandleConfirmQuitGame",       FindBytesForHook(FindFunctionCall(HandleConfirmQuitGame)),  HookHandleConfirmQuitGame]
    ])
    
    MakeEnumHook("GameObject", [
        ["HookOnProcessSpell",              FindBytesForHook(FindFunctionStart(OnProcessSpell)),        HookOnProcessSpell],
        ["HookOnProcessAutoAttack",         FindBytesForHook(FindFunctionStart(ProcessAutoAttack)),     HookOnProcessAutoAttack],
        ["HookOnCreateObject",              FindBytesForHook(FindFunctionCall(OnCreateObject)),         HookOnCreateObject],
        ["HookOnDeleteObject",              FindBytesForHook(FindFunctionCall(OnDeleteObject)),         HookOnDeleteObject],
        ["HookOnIssueOrder",                FindBytesForHook(FindFunctionCall(IssueOrder)),             HookOnIssueOrder],
        ["HookOnPlayAnimation",             FindBytesForHook(FindFunctionStart(PlayAnimation)),         HookOnPlayAnimation],
        ["HookOnBuffAdd",                   FindBytesForHook(FindFunctionStart(OnBuffAdd)),             HookOnBuffAdd],
        ["HookOnBuffRemove",                FindBytesForHook(FindFunctionStart(OnBuffRemove)),          HookOnBuffRemove],
        ["HookOnPlayAnimation",             FindBytesForHook(FindFunctionStart(PlayAnimation)),         HookOnPlayAnimation],

    ])
    
    MakeEnumHook("Spellbook", [
        ["HookOnCastspell",                 FindBytesForHook(FindFunctionCall(SendSpellcastPacket)),    HookOnCastspell],
        ["HookOnStopCast",                  FindBytesForHook(FindFunctionStart(OnStopCast)),            HookOnStopCast],
        ["HookOnCastComplete",              FindBytesForHook(FindFunctionStart(OnCastComplete)),        HookOnCastComplete],
        ["HookOnSpellImpact",               FindBytesForHook(FindFunctionStart(OnSpellImpact)),         HookOnSpellImpact]
    ])

    MakeEnumHook("EventSystem", [
        ["HookOnNotify",                     FindBytesForHook(FindFunctionStart(Notify)),                HookOnNotify]
    ])             

main()