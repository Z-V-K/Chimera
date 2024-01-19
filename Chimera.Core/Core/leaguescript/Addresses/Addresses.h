#pragma once

namespace Addresses {

	enum class Bypass : uintptr_t {
		IntegrityCheckHashesArray	= 0x46AD90,		// 13.15 // SIG:
	
		CastSpellFlag				= 0x2192850,	// 13.24 // SIG: 4C 89 6C 24 38 C6 05 ? ? ? ? ?
		IssueOrderFlag				= 0x21928B8,	// 13.24 // SIG: 40 88 7C 24 20 C7 05 ? ? ? ? ? ? ? ?

		DetectionWatcher1			= 0x2226d20,	// 13.24 // SIG: 4C 8B 05 ? ? ? ? 33 FF // Spellbook functions
		DetectionWatcher2			= 0x221F578,	// 13.24 // SIG: 4C 8B 0D ? ? ? ? D0 C8 // Common to some functions

		GetHealthBarScreenPositionDetection = 0x1c7440, // 13.24 // SIG: E8 ? ? ? ? C7 43 5C 00 00 00 00 
	}; 

	enum class r3dRenderer : uintptr_t
	{
		r3dRendererInstance			= 0x228D1C0,	// 13.24 // SIG: 8B 48 08 85 C9 74 0E
		screenInstance				= 0x221F550,	// 13.24 // SIG: 4C 8B 05 ? ? ? ? 48 8B CE
		screenInstance_W2S			= 0x270,		// 13.24
		WorldToScreen				= 0xE71060,		// 13.24 // SIG: 48 83 EC 38 49 8B C0 
		ViewProjectionMatrix		= 0x2284710,	// 13.24 // SIG: 48 8D 0D ? ? ? ? 0F 10 00
		ViewMatrix					= 0x0,
		ProjectionMatrix			= 0x40,
		RenderUsualSuspects			= 0x60C180,		// 13.24 // SIG: E8 ? ? ? ? 0F 28 CF 49 8B CC
		RenderMouseOvers			= 0x50C7F0,		// 13.24 // SIG: E8 ? ? ? ? 41 80 7C 24 04 00 0F 84 ? ? ? ?
		LoadTexture					= 0xE60990,		// 13.24 // SIG: E8 ? ? ? ? 48 83 BC 24 ? ? ? ? ? 74 41 // string: DATA/Spells/Textures/CircularRangeIndicatorUL.dds
		LoadTextureFirstArg			= 0x221F4C8,	// 13.24 // SIG: 48 8B 35 ? ? ? ? 48 8D 05 ? ? ? ? 48 8B CE // passed to LoadTexture as first arg always
		ZoomCheatDetectionFlag		= 0x225EA34,	// 13.24 // SIG: 0F 85 ? ? ? ? B8 ? ? ? ? C6 05 ? ? ? ? ? 
		RenderEffect				= 0x60B3F0,		// 13.24 // SIG: 40 55 53 57 41 55 48 8D AC 24 E8 FE FF FF

		DrawCircularRangeIndicator = 0x0,			// ?
	};

	enum class ObjectManager : uintptr_t
	{
		ObjectManagerInstance		= 0x221C500,	// 13.24 // SIG: 48 8B 0D ? ? ? ? 0F 28 F1 E8 ? ? ? ?
		GetFirstObject				= 0x3B66B0,		// 13.24 // SIG: E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 89 7C 24 30
		GetNextObject				= 0x3B8220,		// 13.24 // SIG: 4C 8B 49 18 4C 8B 41 20 
		FindObject					= 0x3B4BD0,		// 13.24 // SIG: E8 ? ? ? ? 48 83 78 78 10
		GetNetworkObject			= 0x3B8180,		// 13.24 // SIG: E8 ? ? ? ? 48 8B F0 48 85 C0 75 05 48 8B F3 
	};

	enum class GameObjectAddresses : uintptr_t
	{
		OnCreateObject				= 0x3C7CB0,		// 13.24 // SIG: E8 ? ? ? ? 48 8B 3D ? ? ? ? 8B 9E ? ? ? ?
		OnDeleteObject				= 0x3B2B50,		// 13.24 // SIG: E8 ? ? ? ? 48 C7 43 20 00 00 00 00 48 83 C4 20 5B C3 CC CC CC CC 40 53
		OnCastComplete				= 0x23A260,		// 13.24 // SIG: 48 89 5C 24 ? 57 48 83 EC 20 48 8B F9 48 8B DA 8B 8A ? ? ? ?
		OnProcessSpell				= 0x72C510,		// 13.24 // SIG: 40 53 48 83 EC 30 4C 8B 0A
		OnStopCast					= 0x72C870,		// 13.24 // SIG: 44 88 4C 24 ? 4C 89 44 24 ? 88 54 24 10
		SetPath						= 0x3C8130,		// 13.24 // SIG: E8 ? ? ? ? 4D 8B 66 08 48 63 C5
		OnBuffAdd					= 0x6B5DD0,		// 13.24 // SIG: E8 ? ? ? ? 41 83 7F ? ? 4C 8B AC 24 ? ? ? ? 
		OnBuffRemove				= 0x6B89E0,		// 13.24 // SIG: 4C 8B DC 57 41 57 48 81 EC F8 00 00 00 48 8B F9
		PlayAnimation				= 0x23E3F0,		// 13.24 // SIG: 48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B F2 48 8B F9
		ProcessAutoAttack			= 0x243AE0,		// 13.24 // SIG: E8 ? ? ? ? 83 BD C4 00 00 00 00 0F B6 D8
		GetAttackDelay				= 0x3D65C0,		// 13.24 // SIG: F3 0F 10 89 ? ? ? ? E9 ? ? ? ?
		GetAttackCastDelay			= 0x3D64C0,		// 13.24 // SIG: E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?
		GetBasicAttack				= 0x205A90,		// 13.24 // SIG: E8 ? ? ? ? 48 83 38 00 74 58
		CompareTypeFlags			= 0x2167A0,		// 13.24 // SIG: 0F B6 41 48 4C 8B C9
		GetHealthBarScreenPosition	= 0x8AF300,		// 13.24 // SIG: E8 ?? ?? ?? ?? F3 0F 10 46 ?? 4C 8D 4C 24 ??
		BaseDrawPosition			= 0x208F50,		// 13.24 // SIG: E8 ? ? ? ? EB 06 49 8B 06 
		GetOwnerPlayer				= 0x20C4C0,		// 13.24 // SIG: E8 ? ? ? ? 49 8D 8F D0 02 00 00 48 8B 11 0F B6 18 4C 8B 42 30 48 8D 94 24 08 01 00 00
		GetBaseHealthForLevel		= 0x205890,		// 13.24 // SIG: E8 ? ? ? ? F3 0F 10 B3 B4 14 00 00 // String: "AIBaseCommon::GetBaseHealthForLevel()"
		IsAlive						= 0x2553D0,		// 13.24 // SIG: E8 ? ? ? ? 84 C0 74 35 48 8D 8F ? ? ? ? 
		IsDead						= 0x215890,		// 13.24 // SIG: E8 ? ? ? ? 0F B6 F0 EB 17
		IsClone						= 0x2156E0,		// 13.24 // SIG: 48 8B 81 ? ? ? ? 48 85 C0 74 08 83 78 ? ? 0F 95 C0 C3 // RIGHT ABOVE AIMinionCommon::IsLaneMinion()
		UpdateCharacterDataStack	= 0x1A3C50,		// 13.24 // SIG: E8 ? ? ? ? 41 8B 97 E8 11 00 00
		PushCharacterDataStack		= 0x18D9F0,		// 13.24 // SIG: E8 ? ? ? ? 80 BD 9F 00 00 00 00
		GetCircleIconPortrait		= 0x206C30,		// 13.24 // SIG: E8 ? ? ? ? 48 8B F0 48 8B 00
		GetSquareIconPortrait		= 0x20D9A0,		// 13.24 // SIG: E8 ? ? ? ? 48 8B 30 48 85 F6
		GetTotalRespawnTime			= 0x206F70,		// 13.24 // SIG: 48 8D 91 ? ? ? ? 33 C9 0F B6 42 08 44 0F B6 42 ? F3 0F 10 44 82 ? F3 0F 11 44 24 ? 4D 85 C0 74 28 0F 1F 40 00 66 0F 1F 84 00 ? ? ? ? 48 8B 44 CA ? 48 F7 D0 48 31 44 CC ? 48 FF C1 49 3B C8 72 EB F3 0F 10 44 24 ? 0F B6 42 02 4C 8B C2 84 C0 74 35 B9 ? ? ? ? 48 2B C8 48 83 F9 04 73 27 0F 1F 40 00 0F 1F 84 00 ? ? ? ? 41 0F B6 44 08 ? F6 D0 30 44 0C 08 48 FF C1 48 83 F9 04 72 EB F3 0F 10 44 24 ? C3 CC CC CC CC F3 0F 10 89 ? ? ? ?   // func right above GetRespawnTimeRemaining in vtable. 
		GetRespawnTimeRemaining		= 0x20D0D0,		// 13.24 // SIG: 40 53 48 83 EC 20 48 8B D9 48 81 C1 ? ? ? ? E8 ? ? ? ? 0F B6 83 ? ? ? ?
		GetTimerExpiry				= 0x20E320,		// 13.24 // SIG: 40 56 48 83 EC 40 83 B9 ? ? ? ? ?
		GetGoldGivenOnDeath			= 0x2088A0,		// 13.24 // SIG: F3 0F 2C C9 E9 ?? ?? ?? ??
		SpellslotCanBeUpgraded		= 0x2088A0,		// 13.24 // SIG: E8 ?? ?? ?? ?? 84 C0 74 10 41 89 1F
		BuyItem						= 0x1F3800,		// 13.24 // SIG: 40 55 53 56 41 56 41 57 48 8D 6C
		CreateClientEffect			= 0x6A0560,		// 13.24 // SIG: E8 ?? ?? ?? ?? 48 8B 4D E8 48 85 C9 74 13

		OnBuffUpdate				 = 0x4DB530,	// TO_UPDATE: 13.05 // E8 ? ? ? ? 5B 85 F6
		GetAutoAttackAnimationToPlay = 0x153630,	// TO_UPDATE: 13.05 //
		GetBoundingRadius			 = 0x154b00,	// TO_UPDATE: 13.05 // E8 ? ? ? ? D8 44 24 0C 8B 7C 24 18
		DoEmote						 = 0x694800,	// TO_UPDATE: 13.05 // 8B 0D ? ? ? ? 83 EC ? 8B 49 08 53
		UseObject					 = 0x154e10,	// TO_UPDATE: 13.05 // E8 ? ? ? ? 85 C0 75 26 8B 0D
		SendPingPacket				 = 0x0,			// TO_UPDATE: 12.22 // FF 74 24 0C FF 74 24 0C FF 74 24 0C E8 ? ? ? ? C2
		ShouldDrawTurretRange		 = 0x0,			// ?
	};

	enum class GameClient : uintptr_t
	{
		GameClientInstance			= 0x221F5D0,	// 13.24 // SIG: 48 8B 0D ? ? ? ? 41 8D 51 01 48 89 44 24 20
	};

	enum class GameStartData : uintptr_t
	{
		GameStartDataInstance		= 0x221C508,	// 13.24 // SIG: 48 8B 05 ? ? ? ? 44 39 B0 F4 00 00 00
		GetMissionMode				= 0x472620,		// 13.24 // SIG: E8 ? ? ? ? 48 8B CE 48 8B F8 E8 ? ? ? ? 85 C0 74 38
		GetMapID					= 0x2F8180,		// 13.24 // SIG: E8 ?? ?? ?? ?? 4C 89 7C 24 40 48 8D 4C 24 70
		GetRegion 					= 0x473110,		// 13.24 // SIG: E8 ? ? ? ? 48 8B D8 C7 45 38 00 00 00 00
		GetGameID					= 0x471A20,		// 13.24 // SIG: E8 ? ? ? ? 48 85 C0 44 8D 53 FF
	};

	enum class BuffEntry : uintptr_t
	{
		IsValid						= 0x6B6430,		// 13.24 // SIG: E8 ? ? ? ? 84 C0 75 59 C6 43 50 00 // LITERAL: BuffEntry_IsValid
	};

	enum class ManagerList : uintptr_t
	{
		M_MinionList				= 0x221F590,	// 13.24 // SIG: 48 8B 05 ? ? ? ? F3 0F 10 40 28
		M_HeroList					= 0x221C620,	// 13.24 // SIG: 48 8B 0D ? ? ? ? 48 8D 54 24 ? 33 C0 89 44 24 24 
		M_TurretList				= 0x2225FC0,	// 13.24 // SIG: 48 8B 1D ? ? ? ? 48 8B 5B 28
		M_MissileList				= 0x223A1B0,	// 13.24 // SIG: 4C 8B 05 ? ? ? ? 49 8B 58 08

		M_InhibitorList				= 0x15B5A9C,	// TO_UPDATE: 13.05 // 75 22 6A 01 68 ? ? ? ?
		M_AttackableUnitList		= 0x2522168,	// TO_UPDATE: 13.05 // FF 10 8B 15 ? ? ? ?
	};

	enum class SpellDataInst : uintptr_t // (SpellSlot*)
	{
		GetIconTexture				= 0x6A9E60,		// 13.24 // SIG: 84 D2 75 14
	};

	enum class LocalPlayer : uintptr_t
	{
		LocalPlayerInstance			= 0x223A0B8,	// 13.24 // SIG: 48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1 
		IssueOrder					= 0x218580,		// 13.24 // SIG: E8 ? ? ? ? 8D 43 11

		TryRightClick				= 0x66ba80,		// TO_UPDATE: 13.05 // E8 ? ? ? ? C2 04 00 CC CC CC CC CC 8B 44 24 04 6A 01
	};

	enum class Spellbook : uintptr_t
	{
		SendSpellcastPacket			= 0x727850,		// 13.24 // SIG: E8 ? ? ? ? 4C 8B 64 24 ? 4C 8B 74 24 ? 4C 8B 6C 24 ?
		UpdateChargedSpell			= 0x8B5070,		// 13.24 // SIG: E8 ? ? ? ? B0 01 48 83 C4 28 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC 28 44 0F B6 51 1B 
		OnSpellImpact				= 0x723980,		// 13.24 // SIG: 48 89 5C 24 10 48 89 6C 24 18 57 41 54 41 55 41 56 41 57 48 81
		GetSpellState				= 0x7090B0,		// 13.24 // SIG: E8 ? ? ? ? 48 8B CE 44 8B F8 
		OnDoCast					= 0x23A260, 	// 13.24 // SIG: 48 89 5C 24 08 57 48 83 EC 20 48 8B F9 48 8B DA 8B 8A 1C 01 00 00

		NewCastSpell				= 0x664460,		// TO_UPDATE: 13.05 // 83 EC 08 57 FF 74 24 10
	};

	enum class EventSystem : uintptr_t
	{
		Notify						= 0x386850,		// 13.24 // SIG: E8 ?? ?? ?? ?? FF 86 30 01 00 00
		ConvertEventToName			= 0x376020,		// 13.24 // SIG: 48 63 C1 48 8D 0D ?? ?? ?? ?? 48 8D 04 80
	};

	enum class Game : uintptr_t
	{
		GameVersion					= 0x848640,		// 13.24 // SIG: E8 ? ? ? ? 4C 8B 83 B8 03 00 00
		OnMainLoop					= 0x47DC20,		// 13.24 // SIG: E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 90 F0 02 00 00
		OnWorldDraw					= 0xE919A0,		// 13.24 // SIG: E8 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 59
		OnHUDDraw					= 0x916660,		// 13.24 // SIG: E8 ? ? ? ? EB 4A 48 8B 0D ? ? ? ?
		GameTime					= 0x2226D48,	// 13.24 // SIG: F3 0F 5C 35 ? ? ? ? 0F 28 F8
		HandleConfirmQuitGame		= 0x939A10,		// 13.24 // SIG: E9 ? ? ? ? C6 40 40 16

		PlaySound					= 0x215580,		// TO_UPDATE: 13.05 // 56 8B 74 24 14 83 7E 10 00
	};

	enum class NetClient : uintptr_t
	{
		Instance					= 0x221C4F0,	// 13.24 // SIG: 48 8B 0D ? ? ? ? 48 8D 55 D0 41 B0 01 // Inside gnc // LITERAL: NetClientInstance
		GetPing						= 0x4B1860,		// 13.24 // SIG: E8 ? ? ? ? 8B F8 39 03

		GetNetClientInstance = 0x4A1680,		// INLINED 13.18 // SIG: E8 ? ? ? ? 48 8B 56 F0
	};

	enum class Minimap : uintptr_t
	{
		MinimapInstance				= 0x222C530,	// 13.24 // SIG: 66 89 47 60 48 8B 0D ? ? ? ?
	};

	enum class Zoom : uintptr_t	
	{
		Instance					= 0x2221C28,	// 13.24 // SIG: 48 83 C1 78 48 C7 05 ? ? ? ? ? ? ? ? // LITERAL: ZoomInstance
	};

	enum class Chat : uintptr_t
	{
		ChatInstance				= 0x221F7C0,	// 13.24 // SIG: 75 0E 48 8B 0D ? ? ? ? B2 01
		ChatClient					= 0x223A250,	// 13.24 // SIG: 41 FF D1 48 8B 0D ? ? ? ? 
		MenuGui						= 0x223A090,	// 13.24 // SIG: 48 8B 15 ? ? ? ? C1 E8 04
		PrintChat					= 0x877000,		// 13.24 // SIG: E8 ?? ?? ?? ?? 4C 8B C3 B2 01
		SendChat					= 0x86A0E0,		// 13.24 // SIG: 40 53 48 83 EC 20 48 83 7A 18 10 48 8B DA 72 03 48 8B 1A 48 8B 0D ? ? ? ? 41 B0 01 B2 02
	};

	enum class Hud : uintptr_t
	{	
		HudInstance					= 0x221C510,	// 13.24 // SIG: C6 41 10 01 48 8B 05 ? ? ? ?
	};

	enum class NavMesh : uintptr_t
	{
		NavMeshInstance				= 0x221CA98,  	// 13.24 // SIG: 48 89 05 ? ? ? ? E8 ? ? ? ? B9 0A 00 00 00
		IsNotWall					= 0xDECB20,  	// 13.24 // SIG: E8 ? ? ? ? 44 3A E8 
		GetCellHeight				= 0xDE7AB0,  	// 13.24 // SIG: E8 ? ? ? ? 0F 28 F0 F3 0F 5C B3 B0 37 00 00
		GetCellFlags				= 0xDE66D0,  	// 13.24 // SIG: E8 ? ? ? ? 44 3A EB
		AssignNavCellStateFlags		= 0xDE7890,  	// 13.24 // SIG: E8 ? ? ? ? 44 38 7E 7E
		GetCellLocator				= 0xDE65A0, 	// 13.24 // SIG: E8 ? ? ? ? F3 0F 10 45 A4
		GetCellSize					= 0xD4EB30,  	// 13.24 // SIG: E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? F3 0F 58 05 ?? ?? ?? ??
		GetCellCenter				= 0xDE6490,		// 13.24 // SIG: 48 8D 4C 24 30 E8 ? ? ? ? 8B 08 
		IsInFOW						= 0x2A1A20,  	// 13.24 // SIG: E8 ? ? ? ? 02 C0 88 43 40
	};

	enum class PathControllerCommon : uintptr_t
	{
		BuildNavigationPath			= 0xDE2840,		// 13.24 // SIG: E8 ? ? ? ? 48 85 F6 74 0F 48 8B 8B A0 02 00 00 
		CreatePath					= 0x291900,		// 13.24 // SIG: E8 ? ? ? ? F3 0F 11 73 1C
		SmoothPath					= 0x2B4510,		// 13.24 // SIG: 48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 83 7A 30 00
	};
}