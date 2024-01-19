#pragma once

namespace Enums
{
	enum class CombatType : int {
		Melee = 1,
		Ranged = 2,
	};

	enum class GameObjectTeam : int {
		Unknown = 0,
		Blue = 100,
		Red = 200,
		Neutral = 300,
	};

	enum class RecallState : int {
		Unknown = 0,
		Recall = 6,
		EmpoweredRecall = 11,
		Teleport = 16,
	};

	enum class TypeFlag : int
	{
		Object = (1 << 0),  //0x1
		NeutralCamp = (1 << 1),  //0x2
		DeadObject = (1 << 4),  //0x10
		InvalidObject = (1 << 5),  //0x20
		AIBaseCommon = (1 << 7),  //0x80
		AttackableUnit = (1 << 9),  //0x200
		AI = (1 << 10), //0x400
		Minion = (1 << 11), //0x800
		Hero = (1 << 12), //0x1000
		Turret = (1 << 13), //0x2000
		Unknown0 = (1 << 14), //0x4000
		Missile = (1 << 15), //0x8000
		Unknown1 = (1 << 16), //0x10000
		Building = (1 << 17), //0x20000
		Unknown2 = (1 << 18), //0x40000
	};

	enum class GameObjectType : uint32_t
	{
		Unknown = 0x0,
		NeutralMinionCamp = 0xFE7449A3,
		AIHeroClient = 0xE260302C,
		AIMarker = 0x11F7583D,
		AIMinionClient = 0xCAA58CB2,
		ObjectAttacher = 0x9E317160,
		LevelPropAIClient = 0x12E24BCD,
		AITurretClient = 0xBEBA9102,
		AITurretCommon = 0x70678BD0,
		obj_GeneralParticleEmitter = 0xDD4DE76F,
		GameObject = 0x1FAC8B64,
		MissileClient = 0x9C8ADE94,
		DrawFX = 0x42D144F5,
		UnrevealedTarget = 0xB98F49AF,
		BarracksDampener = 0x60BB49C0,
		Barracks = 0xD1ED70FE,
		AnimatedBuilding = 0x8F83FB9C,
		BuildingClient = 0x3CCABB2E,
		obj_Levelsizer = 0x6F2E6CAC,
		obj_NavPoint = 0x96B0A5E6,
		obj_SpawnPoint = 0xE3E9B36C,
		GrassObject = 0xAA2B7AB2,
		HQ = 0x503AD0D2,
		obj_InfoPoint = 0xF4753AD3,
		LevelPropGameObject = 0x5A730CB9,
		LevelPropSpawnerPoint = 0x4D8B713A,
		Shop = 0xA847E0A9,
		Turret = 0x3D775D09
	};

	enum IssueOrderType : int {
		None = 0x0,
		Hold = 0x1,
		MoveTo = 0x2,
		AttackTo = 0x3,
		TempCastspell = 0x4,
		PetHardAttack = 0x5,
		PetHardMove = 0x6,
		AttackMove = 0x7,
		Taunt = 0x8,
		PetHardReturn = 0x9,
		Stop = 0xA,
		PetHardStop = 0xB,
		Use = 0xC,
		AttackTerrainSustained = 0xD,
		AttackTerrainOnce = 0xE,
		CastSpell = 0xF,
		Unk1 = 0x10,
	};

	enum GameObjectActionState
	{
		CanAttack = 1 << 0,
		CanCrit = 1 << 1,
		CanCast = 1 << 2,
		CanMove = 1 << 3,
		Immovable = 1 << 4,
		Stealthed = 1 << 5,
		Obscured = 1 << 6,
		Taunted = 1 << 7,
		Feared = 1 << 8,
		Fleeing = 1 << 9,
		Supressed = 1 << 10,
		Sleep = 1 << 11,
		Ghosted = 1 << 13,
		Charmed = 1 << 17,
		Slowed = 1 << 24,
	};

	enum class TurretType
	{
		Unknown,
		TierOne,
		TierTwo,
		TierThree,
		TierFour,
	};
}