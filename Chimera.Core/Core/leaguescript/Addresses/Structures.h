#pragma once

namespace Structures {
	enum class GameClient : unsigned int {
		GameState = 0xC
	};

	enum class Chat : unsigned int
	{
		TimesOpen = 0xC90,
		Position = 0xD28,
	};

	enum class r3dRenderer : unsigned int
	{
		DxVersion = 0x4,						// 0x30000 = dx11, 0 = dx9
		RendererSize = 0xC,
	};

	enum class RenderPipelineLOL : unsigned int
	{
		DefaultMouseOverEffectData = 0x2F0,
	};

	enum class MouseOverEffectData : unsigned int
	{
		Color = 0x0,
		Size = 0x34,
		Blur = 0x3C,
	};

	enum class Hud : unsigned int
	{
		Camera = 0x18,
		Cursor = 0x28,
		WindowFocus = 0xB8, // yes = 1; no = 257
	};

	enum class Cursor : unsigned int
	{
		Position = 0x2C,
		LastClickPosition = 0x38,
		HoveredUnitId = 0x4C,
	};

	enum class Minimap : unsigned int
	{
		MinimapHud = 0x320,
		Position = 0x60,
		Size = 0x68,
	};

	enum class GameStartData : unsigned int {
		GameType = 0x118,
		PlayerIp = 0x140,
		GameName = 0x170
	};

	enum class Zoom : unsigned int
	{
		CameraAngle = 0x1B4,
		Value = 0x2B8,
		OtherMaxValue = 0x20,
		MaxValue = 0x28,
	};

	enum class GameObjectVTable : unsigned int {
		GetBoundingRadius = 37,				
		IsVisible = 38,						
		IsZombie = 64,						
		IsAlive = 85,						// 13.20
		GetPathControllerCommon = 160,		
		GetBaseHealth = 168,
		GetRespawnTime = 238,				
		GetRespawnTimeRemaining = 239,		
		IsCastObjectWindingUp = 248,		
		PlayAnimation = 276,				// 13.20		
	};

	enum class GameObject : unsigned int
	{
		Index = 0x10,                               
		Team = 0x3C,                                
		Name = 0x60,                                
		NetworkId = 0xC8,                           
		Position = 0x280,                           
		EffectEmitter = 0x290,						
		Visibility = 0x310,                         
		MissileClient = 0x2E0,                      
		Mana = 0x370,                               
		MaxMana = Mana + 0x18,                      
		IsInvulnerable = 0x520,                     
		IsTargetable = 0xEE0,                       
		RecallState = 0xF70,                        
		Health = 0x1088,                            
		MaxHealth = Health + 0x18,                  
		Shield = 0x10E8,                            
		PhysicalShield = 0x1100,                    
		MagicShield = 0x1118,                       
		CharacterState = 0x10F8,	//13.04 ?
		AbilityHaste = 0x14E0,                      

		CharacterIntermediate = 0x1A20,	// "mBaseAttackDamage" xref func -> 2nd arg (a1 + offset)

		ManaRegen = 0x1FC0,                         
		MagicPenFlat = 0x1E88,                      
		Lethality = 0x1E10,                         
		ArmorPenMultiplier = Lethality + 0x18,      
		MagicPenMultiplier = MagicPenFlat + 0x30,   
		BonusAD = 0x1AE0,                           
		TotalAP = 0x1B40,                           
		BonusAPMultiplier = TotalAP + 0x18,         
		AttackSpeedBonus = 0x1BD0,                  
		AttackSpeedMultiplier = 0x1BB8,             
		BaseAD = 0x1C00,                            
		CritDamageMultiplier = 0x1C78,              
		Crit = 0x1CA8,                              
		Armor = 0x1CF0,                             
		BonusArmor = Armor + 0x18,                  
		MagicRes = BonusArmor + 0x18,               
		BonusMagicRes = MagicRes + 0x18,            
		MovementSpeed = 0x16F4,                     
		AttackRange = 0x1DB0,                       
		HealthRegen = 0x1D50,                       
		Direction = 0x21D8,                         
		CurrentGold = 0x2180,                       
		AccumulatedGold = CurrentGold + 0x18,       
		CombatType = 0x26A8,                        

		// AIHero
		BuffManager = 0x27F8,                       
		SpellBook = 0x2A38,             // First arg SendSpellcastPacket
		CharacterData = 0x35E0,			// second offset with sig: 75 28 48 8B 97 ? ? ? ?
		UnitInfoComponent = 0x3A28,		// Inside GetBaseDrawPosition (uic = a1 + [offset])
		ModelName = 0x38A8,             
		// ...

		// AIHeroClient
		AccumulatedExperience = 0x4030,             
		Level = 0x4048,                             
		LevelUpPoints = 0x4088,                     
		ItemList = 0x40C0,                          
		// ...

		// AIMinionClient
		EncryptedIsLaneMinion = 0x4129,	// AIMinionCommon VTABLE 10 funcs above AIBaseCommon::GetDeathDuration() -> AIMinionCommon::IsLaneMinion()
		EncryptedIsPet = 0x416A,		// AIMinionCommon VTABLE 9 funcs above AIBaseCommon::GetSpellOriginInfo() (48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 81 C1 30 FD FF FF) -> AIMinionCommon::IsPet()
		EncryptedIsWard = 0x4161,		// AIMinionCommon VTABLE 10 funcs above AIBaseCommon::GetSpellOriginInfo() -> AIMinionCommon::IsWard()
		// ...

		SrcIndex = 0x0                  //12.12 TBD Source index i.e Tibbers returns annie Index
	};

	enum class CharacterState : DWORD
	{
		Flags = 0x24
	};

	enum class MissileClient : unsigned int
	{
		SpellInfo = 0x8,

		Slot = 0x10,
		MissileIndex = 0x14,
		CasterName = 0x28,
		CasterIndex = 0x90,
		
		StartPosition = 0xAC,
		EndPosition = StartPosition + 0xC,
		CastPosition = EndPosition + 0xC,

		TargetArray = 0xE8,
		TargetArraySize = TargetArray + 0x8
	};

	enum class PathControllerCommon : unsigned int
	{
		NavigationMesh = 0x2A0,
		NavigationPath = 0x2C0,
		DashSpeed = 0x300,
		IsDashing = 0x324,
		ServerPos = 0x414,
	};

	enum class NavigationPath : unsigned int
	{
		CurrSegment = 0x0,
		NavStart = 0x10,
		NavEnd = NavStart + 0xC,
		NavArray = 0x28,
		NbWaypoints = 0x30
	};

	enum class SpellBook : unsigned int
	{
		ActiveSpell = 0x38,
		FirstSlot = 0x6D0,
	};

	enum class SpellBookVTable : unsigned int
	{
		GetSpellState			= 1,
		GetSpellSlot			= 13
	};

	enum class EffectCreateDataClient : unsigned int {
		EffectHash = 0x8,
		Emitter = 0x10,
	};

	enum class EffectEmitter : unsigned int {
		Data = 0x8,

		Attachment = 0x38,
		TargetAttachment = 0x48
	};

	enum class EffectEmitterData : unsigned int {
		OrientationRight = 0x118,
		OrientationUp = OrientationRight + 0x10,
		OrientationForward = OrientationUp + 0x10
	};

	enum class EffectEmitterAttachment : unsigned int {
		Data = 0x8,
		Object = 0x0,
	};

	enum class CharacterData : unsigned int {
		CharacterHash = 0x18,
		BaseCharacterData = 0x28
	};

	enum CharacterBaseData : unsigned int {
		BaseHealth = 0xB0,
		BaseMana = 0x11C
	};
	
	enum class SpellCastInfo : unsigned int
	{
		SpellData = 0x0,

		SrcIndex = 0x88,

		StartPos = 0xA4,
		EndPos = StartPos + 0xC,
		CastPos = EndPos + 0xC,

		TargetIndex = 0xE0,
		CastDelay = 0xF0,

		IsSpell = 0x10C,				// == 0
		IsSpecialAttack = 0x112,		// == 0
		IsAuto = 0x113,

		Slot = 0x11C,
	};

	enum class SpellSlot : unsigned int
	{
		Level = 0x28,
		ReadyAt = 0x30,
		Ammo = 0x5C,
		AmmoReadyAt = 0x68,
		AmmoCooldown = 0x6C,
		MaxCD = 0x74,
		Damage = 0x90,
		SlotId = 0xF4,

		TargetClient = 0x128,
		SpellData = 0x130,
	};

	enum class SpellData : unsigned int
	{
		SpellDataScript = 0x18,
		SpellName = 0x28,
		SpellDataResource = 0x60,
	};

	enum class SpellDataScript : unsigned int {
		Name = 0x8,
		Hash = 0x18,
	};

	enum class SpellDataResource : unsigned int // TODO; reverse more of this.
	{
		mScriptName = 0x80,				// raw

		mSpellTagsArray = 0xD0,			// ptr
		mSpellTagsArrayLength = 0xD8,

		mDataValues = 0x1F8,			// ptr
		mDataValues_BaseDamage = 0x14,	// raw values, 7 of them

		mSpellCalculations = 0x218,		// ptr to array

		mAnimationName = 0x250,			// ptr to array

		mImgIconName = 0x290,			// ptr to array

		cooldownTime = 0x2F4,			// raw values, 7 of them
		delayCastOffsetPercent = 0x310, // raw
		delayTotalTimePercent = 0x314,	// raw

		mMaxAmmo = 0x3C0,				// raw values, 7 of them
		mAmmoRechargeTime = 0x3F8,		// raw values, 7 of them
		mTurnSpeedScalar = 0x444,		// raw
		castRange = 0x46C,				// raw values, 7 of them
		castRangeDisplayOverride = 0x488, // raw values, 7 of them
		castRadius = 0x4A4,				// raw values, 7 of them
		castConeDistance = 0x4E0,

		mMissileSpec	= 0x4F0,		// ptr
		mMissileSpel_mMissileWidth = 0x8,

		castType = 0x4F8,
		castFrame = 0x4FC,
		missileSpeed = 0x500,
		mLineWidth = 0x550,
		mana = 0x604,
	};

	enum class ItemSlot : unsigned int
	{	
		ItemInfo = 0x10,
	};

	enum class ItemInfo : unsigned int
	{
		ItemData = 0x38,

		Price = 0x44,
		Stacks = 0x44,
	};

	enum class ItemData : unsigned int
	{
		ItemId = 0x9C,
		AbilityHaste = 0x158,
		Health = AbilityHaste + 0x4,
		HealthRegen = 0x16C,
		MovementSpeed = 0x188,
		Armor = 0x194,
		MagicResistance = 0x1B4,
		Ad = 0x1D0,
		Ap = 0x1D8,
		AttackSpeedMultiplier = 0x204,
		ShieldPowerMultiplier = 0x20C,
		Mana = 0x234,
		ManaRegen = 0x244,

		Texture = 0x5A8,
	};
		
	enum class BuffManager : unsigned int
	{
		BuffEntriesArray = 0x18,
		BuffEntriesArrayEnd = 0x20,
	};

	enum class BuffManagerVTable : unsigned int
	{
		HasBuffOfType = 0x1,
	};

	enum class BuffEntry : unsigned int
	{
		BuffData = 0x10,
		BuffCasterData = 0x30,
		BuffOwnerData = 0x40,

		BuffCasterDataCasterHandle = 0x4,

		BuffOwnerObject = 0x8,

		Type = 0x8,
		StartTime = 0x18,
		EndTime = 0x1C,
		CountAlt = 0x38,
		CountInt = 0x8C,
		CountFloat = 0x48,
	};

	enum class BuffData : unsigned int
	{
		Name = 0x8,
		Hash = 0x18,
		Texture = 0x70,
	};

	enum class NavMesh : unsigned int
	{
		NavGrid = 0x8
	};

	enum class NavGrid : unsigned int
	{
		FlagsMap = 0x100,	// AssignNavCellStateFlags
		CellCountX = 0x6B8,	// AssignNavCellStateFlags
		CellCountY = 0x6BC,	// AssignNavCellStateFlags
	};
			
	enum class SpellTargetClient : unsigned int
	{
		CastSpellArgument = 0x8,
		CasterGameObjectIndex = 0x10,
		TargetGameObjectIndex = CasterGameObjectIndex + 0x4,
		SpellStartPosition = TargetGameObjectIndex + 0x4,
		SpellEndPosition = SpellStartPosition + 0xC,
		SpellEndPosition2 = SpellEndPosition + 0xC,
		SpellEndPosition3 = SpellEndPosition2 + 0xC,
	};

	enum class r3dTexture : unsigned int
	{
		TextureName = 0x8,
		TextureData = 0x30,
		UV = 0x40,

		DXTexture = 0x20,	// inside TextureData
	};
}
