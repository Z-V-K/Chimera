#pragma once
#include <string>
#include <vector>
#include <functional>
#include <Windows.h>

#include "Vector.h"
#include "FAIcons.h"

#ifndef _WIN64
#error Wrong architecture. Please use x64.
#endif

#ifndef __clang__
#error Wrong compiler. Please use LLVM.
#endif

#define COL32_R_SHIFT    0
#define COL32_G_SHIFT    8
#define COL32_B_SHIFT    16
#define COL32_A_SHIFT    24
#define COL32_A_MASK     0xFF000000

static inline float ColSaturate(float f) { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
#define F32_TO_INT8_SAT(_VAL) ((int)(ColSaturate(_VAL) * 255.0f + 0.5f))

#define SCRIPT_EXPORT extern "C" __declspec(dllexport)

#pragma region Core
	enum class ScriptType : uint32_t
	{
		Champion,
		Prediction,
		Evade,
		Orbwalker,
		Utility,
		Misc,
		Core
	};
#pragma endregion

#pragma region GameObject
	enum class CharacterHash : uint32_t
	{
		Aatrox = 0x71097207,
		Ahri = 0xD4BD813E,
		Akali = 0x5F193A14,
		Akshan = 0xe4c3b8cc,
		Alistar = 0x7D004170,
		Amumu = 0xC60111F1,
		Anivia = 0xE6318952,
		Annie = 0xF111751D,
		Aphelios = 0x1FC9370D,
		Ashe = 0xDA1E294F,
		AurelionSol = 0x60C9D8ED,
		Azir = 0xDD919622,
		Bard = 0xFFD1E571,
		Belveth = 0x7FE328C,
		Blitzcrank = 0x9D92842A,
		Brand = 0xE8B74EC7,
		Braum = 0xE8BE5089,
		Briar = 0x05D32CA7,
		Caitlyn = 0x601C4B58,
		Camille = 0x6FF5CBEB,
		Cassiopeia = 0x205BB971,
		Chogath = 0x3094E898,
		Corki = 0xA96B4264,
		Darius = 0x52186A32,
		Diana = 0xCDD2B60F,
		DrMundo = 0xEE5915A3,
		Draven = 0xC42DA22C,
		Ekko = 0x904BF10A,
		Elise = 0xA1490494,
		Evelynn = 0x6089E761,
		Ezreal = 0x084DCF93,
		Fiddlesticks = 0x5783643F,
		Fiora = 0x5C944E1B,
		Fizz = 0xBDE5A683,
		Galio = 0x2AC6F678,
		Gangplank = 0x33D903EF,
		Garen = 0x2DB75281,
		Gnar = 0xEEC9BE98,
		Gragas = 0xFF4BDC63,
		Graves = 0x06B2C5EE,
		Gwen = 0xf33c4b19,
		Hecarim = 0xDEFD19BB,
		Heimerdinger = 0xD77595D9,
		Illaoi = 0x90FF0372,
		Irelia = 0xE83E3148,
		Ivern = 0x804569D4,
		Janna = 0xF78D33AA,
		JarvanIV = 0xB1F7EC95,
		Jax = 0x349383C1,
		Jayce = 0xFCECDB84,
		Jhin = 0x7771D5C3,
		Jinx = 0x77F4E689,
		Kaisa = 0x39084661,
		Kalista = 0xE0DB4F6D,
		Karma = 0x3D70D070,
		Karthus = 0x72C6D76E,
		Kassadin = 0x9A84477E,
		Katarina = 0x0381260D,
		Kayle = 0x40E23CBC,
		Kayn = 0xA2963DEB,
		Kennen = 0x454B9583,
		Khazix = 0xBA24D3E5,
		Kindred = 0x30E7F07D,
		Kled = 0xA7ECE380,
		KogMaw = 0xA65585E0,
		KSante = 0x9F6F3186,
		Leblanc = 0xEB2D6693,
		LeeSin = 0xBB34EE8C,
		Leona = 0x39FF4429,
		Lillia = 0xd23b335,
		Lissandra = 0x0884BF49,
		Lucian = 0x97F8A01C,
		Lulu = 0xDAE94192,
		Lux = 0x35A3A7AF,
		Malphite = 0xC1DCEAAA,
		Malzahar = 0x22D7D75A,
		Maokai = 0x8EFB7D38,
		MasterYi = 0xE5A429F2,
		MissFortune = 0x01E5A725,
		Mordekaiser = 0x166C307E,
		Morgana = 0xF537FDDD,
		Milio = 0x3687B676,
		Naafiri = 0x8994331B,
		Nami = 0x2E1EAD2F,
		Nasus = 0x09BBFEFE,
		Nautilus = 0x6C318333,
		Neeko = 0xBCE86672,
		Nidalee = 0x7DA436B4,
		Nilah = 0x7A6C1378,
		Nocturne = 0xC4AADC06,
		Nunu = 0x37F8E38E,
		Olaf = 0x62042582,
		Orianna = 0x70018CA6,
		Ornn = 0x650585C3,
		Pantheon = 0xE51EFF33,
		Poppy = 0x1B74F7BA,
		Pyke = 0x96FBC243,
		Qiyana = 0xd37489d3,
		Quinn = 0x7315CE25,
		Rakan = 0x1568FA09,
		Rammus = 0xA1DBE5ED,
		RekSai = 0x57601883,
		Rell = 0xea312df3,
		Renata = 0xda2a7853,
		Renekton = 0x1C0BE672,
		Rengar = 0xDD0BD0BD,
		Riven = 0x8F0E2B88,
		Rumble = 0xEADFA531,
		Ryze = 0xF4186772,
		Samira = 0xB60D0859,
		Sejuani = 0x887A3ADF,
		Senna = 0x14F7CDAF,
		Seraphine = 0xc2cb5e87,
		Sett = 0x18c000b2,
		Shaco = 0x9A1A73B8,
		Shen = 0x1A2B2B7E,
		Shyvana = 0xF45FC062,
		Singed = 0x02EDAEEE,
		Sion = 0x1AB33D75,
		Sivir = 0xD2FE8B89,
		Skarner = 0x24FE8072,
		Sona = 0x1DA69A2F,
		Soraka = 0x51A4D061,
		Swain = 0x5406B062,
		Sylas = 0xb676fa78,
		Syndra = 0x404673AB,
		TahmKench = 0xD93E9107,
		Taliyah = 0x6B3F0A56,
		Talon = 0x9DCDCAFE,
		Taric = 0xA0BC267F,
		Teemo = 0x5474A0F6,
		Thresh = 0x8E5AD89C,
		Tristana = 0x23CDE228,
		Trundle = 0x25D6A766,
		Tryndamere = 0xDE11375B,
		TwistedFate = 0xD04DE692,
		Twitch = 0xEDC9F793,
		Udyr = 0x755493E8,
		Urgot = 0xF637B92F,
		Varus = 0x28A0E785,
		Vayne = 0x2C0C5245,
		Veigar = 0x4D1B41FE,
		Velkoz = 0xDAB5F5B9,
		Vex = 0x3a803ec9,
		Vi = 0x00761D73,
		Viego = 0x9662a07a,
		Viktor = 0xC04F2C7F,
		Vladimir = 0xBECBD446,
		Volibear = 0x3F2A754A,
		Warwick = 0x08CA82C2,
		MonkeyKing = 0x205D23CA,
		Xayah = 0xB3D80D17,
		Xerath = 0x195002D0,
		XinZhao = 0x0BBB6179,
		Yasuo = 0xF4E41405,
		Yorick = 0xDA9791F5,
		Yuumi = 0x98607FF5,
		Zac = 0x3C747BBC,
		Zed = 0x3C787CB9,
		Zeri = 0x5E6DB562,
		Ziggs = 0xA7103B84,
		Zilean = 0x40169635,
		Zoe = 0x3C827F30,
		Zyra = 0x6846EB6E,
		Yone = 0x34cf7ead,
		PracticeTool_TargetDummy = 0x6a9da18b,
		SRU_Plant_Health = 0xc3479cd9,
		SRU_Plant_Satchel = 0xe8814ff5,
		SRU_Plant_Vision = 0x4d61e805,
		SRU_Dragon_Air = 0x11d34e07,
		SRU_Dragon_Earth = 0x606dcd87,
		SRU_Dragon_Fire = 0x99a947d9,
		SRU_Dragon_Water = 0x27f996f4,
		SRU_Dragon_Hextech = 0xa076eece,
		SRU_Dragon_Elder = 0x5944e907,
		SRU_Dragon_Chemtech = 0xf956a026,
		ShacoBox = 0x4ac2e173,
		JhinTrap = 0x1c23c910,
		CaitlynTrap = 0xaacc89a5,
		TeemoMushroom = 0x2b2ff5ae,
		YellowTrinket = 0x40d7e043,
		JammerDevice = 0x8223b6ba,
		BlueTrinket = 0xe20532fd,
		SightWard = 0x7C1BCAD9,
		S5Test_WardCorpse = 0x3d5dc843,
		Sru_CrabWard = 0x9dc6e715,
		Sru_Crab = 0x2db77af9,
		SRU_KrugMiniMini = 0xa8245c50,
		SRU_KrugMini = 0xf8123c99,
		SRU_Krug = 0xa20205e2,
		SRU_Gromp = 0xd1c19b7e,
		SRU_Murkwolf = 0x621947dc,
		SRU_MurkwolfMini = 0x9a1d4493,
		SRU_Razorbeak = 0x244e9932,
		SRU_RazorbeakMini = 0xa2c97fe9,
		SRU_Blue = 0xfc505223,
		SRU_Red = 0x9ca35508,
		SRU_RiftHerald = 0xddaf53d2,
		SRU_Baron = 0x68ac12c9,
		SRUAP_Turret_Order1 = 0xc57b1d38,
		SRUAP_Turret_Order2 = 0xc57b1d39,
		SRUAP_Turret_Order3 = 0xc57b1d3a,
		SRUAP_Turret_Chaos1 = 0x8d840146,
		SRUAP_Turret_Chaos2 = 0x8d840147,
		SRUAP_Turret_Chaos3 = 0x8d840148,
		SRUAP_Turret_Order4 = 0xc57b1d3b,
		SRUAP_Turret_Chaos4 = 0x8d840149,
		SRUAP_Turret_Order5 = 0xc57b1d3c,
		PreSeason_Turret_Shield = 0xc1b8c07f,
		HA_AP_OrderTurret = 0x37085ad4,
		HA_AP_OrderTurret2 = 0xe5e25a5e,
		HA_AP_OrderTurret3 = 0xe5e25a5f,
		HA_AP_ChaosTurret = 0x3609c846,
		HA_AP_ChaosTurret2 = 0x14ae496c,
		HA_AP_ChaosTurret3 = 0x14ae496d,
		HA_AP_OrderShrineTurret = 0x2678e477,
		HA_AP_ChaosTurretShrine = 0x2cbcb369,
		SRUAP_MageCrystal = 0x632b992a,
		SRU_ChaosMinionMelee = 0xb87bb4c7,
		SRU_ChaosMinionRanged = 0xd86ea814,
		SRU_OrderMinionMelee = 0xd11193b9,
		SRU_OrderMinionRanged = 0xc44285a2,
		SRU_OrderMinionSiege = 0x1f46a4b2,
		SRU_ChaosMinionSiege = 0x6b0c5c0,
		SRU_OrderMinionSuper = 0x530117c0,
		SRU_ChaosMinionSuper = 0x3a6b38ce,
		HA_OrderMinionMelee = 0xea51b9f6,
		HA_OrderMinionRanged = 0x2148eea5,
		HA_ChaosMinionMelee = 0xd1bbdb04,
		HA_ChaosMinionRanged = 0x35751117,
		HA_OrderMinionSiege = 0x3886caef,
		HA_ChaosMinionSiege = 0x1ff0ebfd,
		HA_OrderMinionSuper = 0x6c413dfd,
		HA_ChaosMinionSuper = 0x53ab5f0b,
		SRU_RiftHerald_Relic = 0xc3cdda6,
		SRU_CampRespawnMarker = 0x3101c878,
		SRU_BaronSpawn = 0x8467c712,
		TestCubeRender = 0xcb00303d,
		SRU_RiftHerald_Mercenary = 0x7ff87da9,
		SRU_PlantRespawnMarker = 0x1a6947a0,
		TestCubeRender10Vision = 0x794d3be4,
		AnnieTibbers = 0x51dae4d4,
		OriannaBall = 0x1e070aa5,
		ShenSpirit = 0xc40cee4f,
		LuluFaerie = 0x1e6ee216,
		ZacRebirthBloblet = 0x2048248e,
		YorickGhoul = 0x5783A104,
		HA_AP_Poro = 0x2c0d32a6,
		HA_AP_PoroSpawner = 0x89620a42,
		HA_AP_HealthRelic = 0xda54bc8d,
		ZyraThornPlant = 0x34B09A22,
		ZyraGraspingPlant = 0x71DC5EAE,
		Blade = 0x794D3BE4,
		Barrel = 0x7B575CB5,
		SennaSoul = 0x924D5AA2,
		ControlWard = 0x8223B6BA,    
		SupportItem = 0x7C1BCAD9,  
		GhostPoro = 0x97648C10,  
		ZombieWard = 0x55814507,
		FiddleSticksTrinket = 0x5783643F,

		Unknown = 0,
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

	enum class GameObjectTeam : int
	{
		Unknown = 0,
		Blue = 100,
		Red = 200,
		Neutral = 300,
	};

	enum class TypeFlag : int
	{
		Object = 1 << 0,
		NeutralCamp = 1 << 1,
		DeadObject = 1 << 4, 
		InvalidObject = 1 << 5, 
		AIBaseCommon = 1 << 7,  
		AttackableUnit = 1 << 9,  
		AI = 1 << 10,
		AIMinionClient = 1 << 11,
		AIHeroClient = 1 << 12,
		AITurretClient = 1 << 13,
		AIMissileClient = 1 << 15,
		Building = 1 << 17,
	};

	DEFINE_ENUM_FLAG_OPERATORS(TypeFlag)

	enum class RecallState : int
	{
		Unknown = 0,
		Recall = 6,
		EmpoweredRecall = 11,
		Teleport = 16,
	};

#pragma endregion

#pragma region Cellflags
	enum class CellFlags : unsigned int
	{
		None = 0,
		Grass = 0x1,
		Wall = 0x2,
		Building = 0x46,
		Prop = 0x80,
		PropGrass = 0x81,
		PropWall = 0x82,
		UnkGrass = 0xC1,
		UnkWall = 0xC2,
		GlobalVision = 0x100
	};

	DEFINE_ENUM_FLAG_OPERATORS(CellFlags)

#pragma endregion

#pragma region BuffManager

	enum class BuffType : unsigned char
	{
		Internal = 0,
		Aura = 1,
		CombatEnchancer = 2,
		CombatDehancer = 3,
		SpellShield = 4,
		Stun = 5,
		Invisibility = 6,
		Silence = 7,
		Taunt = 8,
		Berserk = 9,
		Polymorph = 10,
		Slow = 11,
		Snare = 12,
		Damage = 13,
		Heal = 14,
		Haste = 15,
		SpellImmunity = 16,
		PhysicalImmunity = 17,
		Invulnerability = 18,
		AttackSpeedSlow = 19,
		NearSight = 20,
		Currency = 21,
		Fear = 22,
		Charm = 23,
		Poison = 24,
		Suppression = 25,
		Blind = 26,
		Counter = 27,
		Shred = 28,
		Flee = 29,
		Knockup = 30,
		Knockback = 31,
		Disarm = 32,
		Grounded = 33,
		Drowsy = 34,
		Asleep = 35,
		Obscured = 36,
		ClickproofToEnemies = 37,
		UnKillable = 38,
	};

#pragma endregion

#pragma region Items
	enum class ItemId : uint32_t
	{
		Unknown = 0,
		Boots = 1001,
		Faerie_Charm = 1004,
		Rejuvenation_Bead = 1006,
		Giants_Belt = 1011,
		Cloak_of_Agility = 1018,
		Blasting_Wand = 1026,
		Sapphire_Crystal = 1027,
		Ruby_Crystal = 1028,
		Cloth_Armor = 1029,
		Chain_Vest = 1031,
		Null_Magic_Mantle = 1033,
		Emberknife = 1035,
		Long_Sword = 1036,
		Pickaxe = 1037,
		B_F_Sword = 1038,
		Hailblade = 1039,
		Obsidian_Edge = 1040,
		Dagger = 1042,
		Recurve_Bow = 1043,
		Amplifying_Tome = 1052,
		Vampiric_Scepter = 1053,
		Dorans_Shield = 1054,
		Dorans_Blade = 1055,
		Dorans_Ring = 1056,
		Negatron_Cloak = 1057,
		Needlessly_Large_Rod = 1058,
		Dark_Seal = 1082,
		Cull = 1083,
		Scorchclaw_Pup = 1101,
		Gustwalker_Hatchling = 1102,
		Mosstomper_Seedling = 1103,
		Eye_of_the_Herald = 1104,
		Penetrating_Bullets = 1500,
		Fortification = 1501,
		Reinforced_Armor = 1502,
		Wardens_Eye = 1503,
		Vanguard = 1504,
		Lightning_Rod = 1505,
		Reinforced_Armor_2 = 1506,
		Overcharged = 1507,
		Anti_tower_Socks = 1508,
		Gusto = 1509,
		Phreakish_Gusto = 1510,
		Super_Mech_Armor = 1511,
		Super_Mech_Power_Field = 1512,
		Turret_Plating = 1515,
		Structure_Bounty = 1516,
		Structure_Bounty_2 = 1517,
		Structure_Bounty_3 = 1518,
		Structure_Bounty_4 = 1519,
		OvererchargedHA = 1520,
		Fortification_2 = 1521,
		Tower_Power_Up = 1522,
		Health_Potion = 2003,
		Total_Biscuit_of_Everlasting_Will = 2010,
		Kircheis_Shard = 2015,
		Steel_Sigil = 2019,
		Refillable_Potion = 2031,
		Corrupting_Potion = 2033,
		Guardians_Amulet = 2049,
		Guardians_Shroud = 2050,
		Guardians_Horn = 2051,
		Poro_Snax = 2052,
		Control_Ward = 2055,
		Shurelyas_Battlesong = 2065,
		Elixir_of_Iron = 2138,
		Elixir_of_Sorcery = 2139,
		Elixir_of_Wrath = 2140,
		Cappa_Juice = 2141,
		Juice_of_Power = 2142,
		Juice_of_Vitality = 2143,
		Juice_of_Haste = 2144,
		Guardians_Horn_Arena = 222051,
		Shurelyas_Battlesong_Arena = 222065,
		Evenshroud_Arena = 223001,
		Archangels_Staff_Arena = 223003,
		Manamune_Arena = 223004,
		Berserkers_Greaves_Arena = 223006,
		Boots_of_Swiftness_Arena = 223009,
		Chemtech_Putrifier_Arena = 223011,
		Sorcerers_Shoes_Arena = 223020,
		Guardian_Angel_Arena = 223026,
		Infinity_Edge_Arena = 223031,
		Mortal_Reminder_Arena = 223033,
		Lord_Dominiks_Regards_Arena = 223036,
		Seraphs_Embrace_Arena = 223040,
		Muramana_Arena = 223042,
		Phantom_Dancer_Arena = 223046,
		Plated_Steelcaps_Arena = 223047,
		Zekes_Convergence_Arena = 223050,
		Steraks_Gage_Arena = 223053,
		Spirit_Visage_Arena = 223065,
		Sunfire_Aegis_Arena = 223068,
		Black_Cleaver_Arena = 223071,
		Bloodthirster_Arena = 223072,
		Ravenous_Hydra_Arena = 223074,
		Thornmail_Arena = 223075,
		Trinity_Force_Arena = 223078,
		Heartsteel_Arena = 223084,
		Runaans_Hurricane_Arena = 223085,
		Statikk_Shiv_Arena = 223087,
		Rabadons_Deathcap_Arena = 223089,
		Wits_End_Arena = 223091,
		Rapid_Firecannon_Arena = 223094,
		Stormrazor_Arena = 223095,
		Lich_Bane_Arena = 223100,
		Banshees_Veil_Arena = 223102,
		Redemption_Arena = 223107,
		Knights_Vow_Arena = 223109,
		Frozen_Heart_Arena = 223110,
		Mercurys_Treads_Arena = 223111,
		Guardians_Orb_Arena = 223112,
		Nashors_Tooth_Arena = 223115,
		Rylais_Crystal_Scepter_Arena = 223116,
		Winters_Approach_Arena = 223119,
		Fimbulwinter_Arena = 223121,
		Guinsoos_Rageblade_Arena = 223124,
		Void_Staff_Arena = 223135,
		Mercurial_Scimitar_Arena = 223139,
		Youmuus_Ghostblade_Arena = 223142,
		Randuins_Omen_Arena = 223143,
		Hextech_Rocketbelt_Arena = 223152,
		Blade_of_The_Ruined_King_Arena = 223153,
		Maw_of_Malmortius_Arena = 223156,
		Zhonyas_Hourglass_Arena = 223157,
		Ionian_Boots_of_Lucidity_Arena = 223158,
		Spear_Of_Shojin_Arena = 223161,
		Morellonomicon_Arena = 223165,
		Guardians_Blade_Arena = 223177,
		Hullbreaker_Arena = 223181,
		Guardians_Hammer_Arena = 223184,
		Guardians_Dirk_Arena = 223185,
		Locket_of_the_Iron_Solari_Arena = 223190,
		Gargoyle_Stoneplate_Arena = 223193,
		Mikaels_Blessing_Arena = 223222,
		Ardent_Censer_Arena = 223504,
		Essence_Reaver_Arena = 223508,
		Dead_Mans_Plate_Arena = 223742,
		Titanic_Hydra_Arena = 223748,
		Edge_of_Night_Arena = 223814,
		Imperial_Mandate_Arena = 224005,
		Force_of_Nature_Arena = 224401,
		Horizon_Focus_Arena = 224628,
		Cosmic_Drive_Arena = 224629,
		Riftmaker_Arena = 224633,
		Night_Harvester_Arena = 224636,
		Demonic_Embrace_Arena = 224637,
		Crown_of_the_Shattered_Queen_Arena = 224644,
		Shadowflame_Arena = 224645,
		Silvermere_Dawn_Arena = 226035,
		Deaths_Dance_Arena = 226333,
		Chempunk_Chainsword_Arena = 226609,
		Staff_of_Flowing_Water_Arena = 226616,
		Moonstone_Renewer_Arena = 226617,
		Echoes_of_Helia_Arena = 226620,
		Goredrinker_Arena = 226630,
		Stridebreaker_Arena = 226631,
		Divine_Sunderer_Arena = 226632,
		Liandrys_Anguish_Arena = 226653,
		Ludens_Tempest_Arena = 226655,
		Everfrost_Arena = 226656,
		Rod_of_Ages_Arena = 226657,
		Iceborn_Gauntlet_Arena = 226662,
		Turbo_Chemtank_Arena = 226664,
		JakSho_The_Protean_Arena = 226665,
		Radiant_Virtue_Arena = 226667,
		Galeforce_Arena = 226671,
		Kraken_Slayer_Arena = 226672,
		Immortal_Shieldbow_Arena = 226673,
		Navori_Quickblades_Arena = 226675,
		The_Collector_Arena = 226676,
		Duskblade_of_Draktharr_Arena = 226691,
		Eclipse_Arena = 226692,
		Prowlers_Claw_Arena = 226693,
		Seryldas_Grudge_Arena = 226694,
		Serpents_Fang_Arena = 226695,
		Axiom_Arc_Arena = 226696,
		Syzygy_Arena = 227001,
		Draktharrs_Shadowcarver_Arena = 227002,
		Frozen_Fist_Arena = 227005,
		Typhoon_Arena = 227006,
		Icathias_Curse_Arena = 227009,
		Vespertide_Arena = 227010,
		Upgraded_Aeropack_Arena = 227011,
		Liandrys_Lament_Arena = 227012,
		Eye_of_Luden_Arena = 227013,
		Eternal_Winter_Arena = 227014,
		Ceaseless_Hunger_Arena = 227015,
		Dreamshatter_Arena = 227016,
		Deicide_Arena = 227017,
		Infinity_Force_Arena = 227018,
		Reliquary_of_the_Golden_Dawn_Arena = 227019,
		Shurelyas_Requiem_Arena = 227020,
		Starcaster_Arena = 227021,
		Equinox_Arena = 227023,
		Caesura_Arena = 227024,
		Leviathan_Arena = 227025,
		The_Unspoken_Parasite_Arena = 227026,
		Primordial_Dawn_Arena = 227027,
		Infinite_Convergence_Arena = 227028,
		Youmuus_Wake_Arena = 227029,
		Seething_Sorrow_Arena = 227030,
		Edge_of_Finality_Arena = 227031,
		Flicker_Arena = 227032,
		Cry_of_the_Shrieking_City_Arena = 227033,
		Anathemas_Chains_Arena = 228001,
		Abyssal_Mask_Arena = 228020,
		Minion_Dematerializer = 2403,
		Commencing_Stopwatch = 2419,
		Stopwatch = 2420,
		Broken_Stopwatch = 2421,
		Slightly_Magical_Footwear = 2422,
		Slightly_Magical_Footware = 2422,
		Perfectly_Timed_Stopwatch = 2423,
		Broken_Stopwatch_2 = 2424,
		Evenshroud = 3001,
		Archangels_Staff = 3003,
		Manamune = 3004,
		Ghostcrawlers = 3005,
		Berserkers_Greaves = 3006,
		Boots_of_Swiftness = 3009,
		Chemtech_Putrifier = 3011,
		Chalice_of_Blessing = 3012,
		Sorcerers_Shoes = 3020,
		Lifewell_Pendant = 3023,
		Glacial_Buckler = 3024,
		Guardian_Angel = 3026,
		Infinity_Edge = 3031,
		Mortal_Reminder = 3033,
		Last_Whisper = 3035,
		Lord_Dominiks_Regards = 3036,
		Atmas_Reckoning = 3039,
		Seraphs_Embrace = 3040,
		Mejais_Soulstealer = 3041,
		Muramana = 3042,
		Phage = 3044,
		Phantom_Dancer = 3046,
		Plated_Steelcaps = 3047,
		Zekes_Convergence = 3050,
		Hearthbound_Axe = 3051,
		Steraks_Gage = 3053,
		Sheen = 3057,
		Spirit_Visage = 3065,
		Winged_Moonplate = 3066,
		Kindlegem = 3067,
		Sunfire_Aegis = 3068,
		Tear_of_the_Goddess = 3070,
		Black_Cleaver = 3071,
		Bloodthirster = 3072,
		Ravenous_Hydra = 3074,
		Thornmail = 3075,
		Bramble_Vest = 3076,
		Tiamat = 3077,
		Trinity_Force = 3078,
		Wardens_Mail = 3082,
		Warmogs_Armor = 3083,
		Heartsteel = 3084,
		Runaans_Hurricane = 3085,
		Zeal = 3086,
		Statikk_Shiv = 3087,
		Rabadons_Deathcap = 3089,
		Wits_End = 3091,
		Rapid_Firecannon = 3094,
		Stormrazor = 3095,
		Lich_Bane = 3100,
		Banshees_Veil = 3102,
		Aegis_of_the_Legion = 3105,
		Redemption = 3107,
		Fiendish_Codex = 3108,
		Knights_Vow = 3109,
		Frozen_Heart = 3110,
		Mercurys_Treads = 3111,
		Guardians_Orb = 3112,
		Aether_Wisp = 3113,
		Forbidden_Idol = 3114,
		Nashors_Tooth = 3115,
		Rylais_Crystal_Scepter = 3116,
		Mobility_Boots = 3117,
		Winters_Approach = 3119,
		Fimbulwinter = 3121,
		Executioners_Calling = 3123,
		Guinsoos_Rageblade = 3124,
		Deathfire_Grasp = 3128,
		Caulfields_Warhammer = 3133,
		Serrated_Dirk = 3134,
		Void_Staff = 3135,
		Mercurial_Scimitar = 3139,
		Quicksilver_Sash = 3140,
		Youmuus_Ghostblade = 3142,
		Randuins_Omen = 3143,
		Hextech_Alternator = 3145,
		Hextech_Gunblade = 3146,
		Hextech_Rocketbelt = 3152,
		Blade_of_the_Ruined_King = 3153,
		Hexdrinker = 3155,
		Maw_of_Malmortius = 3156,
		Zhonyas_Hourglass = 3157,
		Ionian_Boots_of_Lucidity = 3158,
		Spear_Of_Shojin = 3161,
		Morellonomicon = 3165,
		Zephyr = 3172,
		Guardians_Blade = 3177,
		Umbral_Glaive = 3179,
		Hullbreaker = 3181,
		Guardians_Hammer = 3184,
		Locket_of_the_Iron_Solari = 3190,
		Seekers_Armguard = 3191,
		Gargoyle_Stoneplate = 3193,
		Spectres_Cowl = 3211,
		Mikaels_Blessing = 3222,
		Scarecrow_Effigy = 3330,
		Stealth_Ward = 3340,
		Arcane_Sweeper = 3348,
		Lucent_Singularity = 3349,
		Farsight_Alteration = 3363,
		Oracle_Lens = 3364,
		Your_Cut = 3400,
		Rite_Of_Ruin = 3430,
		Ardent_Censer = 3504,
		Essence_Reaver = 3508,
		Eye_of_the_Herald_2 = 3513,
		Kalistas_Black_Spear = 3599,
		Kalistas_Black_Spear_2 = 3600,
		Dead_Mans_Plate = 3742,
		Titanic_Hydra = 3748,
		Crystalline_Bracer = 3801,
		Lost_Chapter = 3802,
		Catalyst_of_Aeons = 3803,
		Edge_of_Night = 3814,
		Spellthiefs_Edge = 3850,
		Frostfang = 3851,
		Shard_of_True_Ice = 3853,
		Steel_Shoulderguards = 3854,
		Runesteel_Spaulders = 3855,
		Pauldrons_of_Whiterock = 3857,
		Relic_Shield = 3858,
		Targons_Buckler = 3859,
		Bulwark_of_the_Mountain = 3860,
		Spectral_Sickle = 3862,
		Harrowing_Crescent = 3863,
		Black_Mist_Scythe = 3864,
		Fire_at_Will = 3901,
		Deaths_Daughter = 3902,
		Raise_Morale = 3903,
		Oblivion_Orb = 3916,
		Spectral_Cutlass = 4004,
		Imperial_Mandate = 4005,
		Bloodletters_Curse = 4010,
		Force_of_Nature = 4401,
		The_Golden_Spatula = 4403,
		Horizon_Focus = 4628,
		Cosmic_Drive = 4629,
		Blighting_Jewel = 4630,
		Verdant_Barrier = 4632,
		Riftmaker = 4633,
		Leeching_Leer = 4635,
		Night_Harvester = 4636,
		Demonic_Embrace = 4637,
		Watchful_Wardstone = 4638,
		Stirring_Wardstone = 4641,
		Bandleglass_Mirror = 4642,
		Vigilant_Wardstone = 4643,
		Crown_of_the_Shattered_Queen = 4644,
		Shadowflame = 4645,
		Ironspike_Whip = 6029,
		Silvermere_Dawn = 6035,
		Deaths_Dance = 6333,
		Chempunk_Chainsword = 6609,
		Staff_of_Flowing_Water = 6616,
		Moonstone_Renewer = 6617,
		Echoes_of_Helia = 6620,
		Goredrinker = 6630,
		Stridebreaker = 6631,
		Divine_Sunderer = 6632,
		Liandrys_Anguish = 6653,
		Ludens_Tempest = 6655,
		Everfrost = 6656,
		Rod_of_Ages = 6657,
		Bamis_Cinder = 6660,
		Iceborn_Gauntlet = 6662,
		Turbo_Chemtank = 6664,
		JakSho_The_Protean = 6665,
		Radiant_Virtue = 6667,
		Noonquiver = 6670,
		Galeforce = 6671,
		Kraken_Slayer = 6672,
		Immortal_Shieldbow = 6673,
		Navori_Quickblades = 6675,
		The_Collector = 6676,
		Rageknife = 6677,
		Duskblade_of_Draktharr = 6691,
		Eclipse = 6692,
		Prowlers_Claw = 6693,
		Seryldas_Grudge = 6694,
		Serpents_Fang = 6695,
		Axiom_Arc = 6696,
		Syzygy = 7001,
		Draktharrs_Shadowcarver = 7002,
		Frozen_Fist = 7005,
		Typhoon = 7006,
		Bloodward = 7008,
		Icathias_Curse = 7009,
		Vespertide = 7010,
		Upgraded_Aeropack = 7011,
		Liandrys_Lament = 7012,
		Eye_of_Luden = 7013,
		Eternal_Winter = 7014,
		Ceaseless_Hunger = 7015,
		Dreamshatter = 7016,
		Deicide = 7017,
		Infinity_Force = 7018,
		Reliquary_of_the_Golden_Dawn = 7019,
		Shurelyas_Requiem = 7020,
		Starcaster = 7021,
		Equinox = 7023,
		Caesura = 7024,
		Leviathan = 7025,
		The_Unspoken_Parasite = 7026,
		Primordial_Dawn = 7027,
		Infinite_Convergence = 7028,
		Youmuus_Wake = 7029,
		Seething_Sorrow = 7030,
		Edge_of_Finality = 7031,
		Flicker = 7032,
		Cry_of_the_Shrieking_City = 7033,
		Gangplank_Placeholder = 7050,
		Anathemas_Chains = 8001,
		Abyssal_Mask = 8020
	};
#pragma endregion

#pragma region
	enum class TurretType
	{
		Unknown,
		TierOne,
		TierTwo,
		TierThree,
		TierFour
	};
#pragma endregion

#pragma region Prediction
	enum class CollisionObject
	{
		Minions,
		Heroes,
		Allies,
		YasuoWall, // yasuo, samira
		GameWall,
	};

	enum class HitChance
	{
		OutOfRange,
		Collision,
		Impossible,
		Low,
		Medium,
		High,
		VeryHigh,
		Dashing,
		Immobile
	};
#pragma endregion

#pragma region AntiGapcloser
	enum class GapCloserType
	{
		Skillshot,
		Targeted,
		Item
	};
#pragma endregion

#pragma region Spells
	enum class SkillshotType : int {
		Line,
		Circle,
		Cone
	};

	enum class SpellState : int
	{
		Unknown = -1,
		Ready = 0,
		NotAvailable = 4,
		Supressed = 8,
		NotLearned = 12,
		Channeling = 24,
		Cooldown = 32,
		NoMana = 64,
	};

	DEFINE_ENUM_FLAG_OPERATORS(SpellState)

	enum class DamageType : int {
		Raw,
		Physical,
		Magical,
		Mixed
	};

	enum class SlotId : int
	{
		Unknown = -1,
		Q = 0,
		W = 1,
		E = 2,
		R = 3,
		Summoner1,
		Summoner2,
		Item1,
		Item2,
		Item3,
		Item4,
		Item5,
		Item6,
		Item_Trinket,
		Recall,
		SpecialAttack = 45,
		SpecialSpell1 = 48,
		Auto1 = 64,
		Auto2 = 65,
		Auto3 = 66,
	};
#pragma endregion

#pragma region Menu
	enum class TabCategory
	{
		core,
		script,
		utils,
		misc
	};
#pragma endregion

#pragma region Events
	enum class EventType : int
	{
		OnWndProc = 1,
		OnTick,
		OnSlowTick,			// once every 30 ticks, so it gets called ~30 times per sec.
		OnDraw,
		OnCreateObject,
		OnDeleteObject,
		OnProcessSpellCast,
		OnIssueOrder,
		OnCastSpell,
		OnStopCast,
		OnCastComplete,
		OnDrawEnvironment,
		OnSpellImpact,
		OnPlayAnimation,
		OnBuffGainLose,
		OnSetPath,
		OnProcessAutoAttack,
		OnNotifyEvent,
		OnBeforeAttackOrbwalker,
		OnAfterAttackOrbwalker,
		OnBeforeMoveOrbwalker,
		OnAfterMoveOrbwalker,
	};
#pragma endregion

#pragma region IssueOrder
	enum class IssueOrderType : int
	{
		None = 0x0,
		Hold = 0x1,
		MoveTo = 0x2,
		AttackTo = 0x3,
		AttackMove = 0x7,
		Stop = 0xA,
	};
#pragma endregion

#pragma region MenuEntry
	enum class EntryType : int
	{
		menu,
		checkbox,
		slider,
		slider_float,
		combo,
		color,
		button,
		key
	};
#pragma endregion

#pragma region Orbwalker
	enum class OrbwalkerMode : uint32_t
	{
		None = 0,
		Combo = 1 << 0,
		LaneClear = 1 << 1,
		Harass = 1 << 2,
		LastHit = 1 << 3,
		Flee = 1 << 4
	};

	DEFINE_ENUM_FLAG_OPERATORS(OrbwalkerMode)
#pragma endregion

#pragma region Hash
	constexpr uint8_t char_to_lower(uint8_t input)
	{
		if (static_cast<uint8_t>(input - 0x41) > 0x19u)
			return input;

		return input + 0x20;
	}

	constexpr uint32_t const hash_sdbm(const char* str)
	{
		uint32_t hash = 0;

		for (auto i = 0u; str[i]; ++i)
		{
			hash = hash * 65599 + char_to_lower(str[i]);
		}

		return hash;
	}

	constexpr uint32_t const hash_fnv1a(const char* str)
	{
		uint32_t hash = 0x811C9DC5;

		for (auto i = 0u; str[i]; ++i)
		{
			hash = 16777619 * (hash ^ char_to_lower(str[i]));
		}

		return hash;
	}

	#define sdbm_hash(str) (std::integral_constant<uint32_t, hash_sdbm(str)>::value)
	#define fnv1a_hash(str) (std::integral_constant<uint32_t, hash_fnv1a(str)>::value)

	#define spell_hash(str) fnv1a_hash(str)
	#define buff_hash(str) fnv1a_hash(str)
	#define character_hash(str) sdbm_hash(str)
#pragma endregion

class Color
{
	float x, y, z, w;

public:
	Color() { };
	Color(byte r, byte g, byte b, byte a = 255) { float sc = 1.0f / 255.0f; x = (float)r * sc; y = (float)g * sc; z = (float)b * sc; w = (float)a * sc; }
	Color(uint32_t rgba) { float sc = 1.0f / 255.0f; x = (float)((rgba >> COL32_R_SHIFT) & 0xFF) * sc; y = (float)((rgba >> COL32_G_SHIFT) & 0xFF) * sc; z = (float)((rgba >> COL32_B_SHIFT) & 0xFF) * sc; w = (float)((rgba >> COL32_A_SHIFT) & 0xFF) * sc; }

	operator uint32_t() const
	{
		uint32_t out;
		out = ((uint32_t)F32_TO_INT8_SAT(x)) << COL32_R_SHIFT;
		out |= ((uint32_t)F32_TO_INT8_SAT(y)) << COL32_G_SHIFT;
		out |= ((uint32_t)F32_TO_INT8_SAT(z)) << COL32_B_SHIFT;
		out |= ((uint32_t)F32_TO_INT8_SAT(w)) << COL32_A_SHIFT;
		return out;
	}
};

typedef void Texture;

struct ItemTexture
{
	Texture* texture;
	Vec4 uv;

	Vec2 get_uv_min() const
	{
		return { uv.x, uv.y };
	}

	Vec2 get_uv_max() const
	{
		return { uv.z, uv.w };
	}

	bool is_valid() const
	{
		return texture != nullptr;
	}
};

class SDK;
class MissileClient;
class GameObject;
class Buff;
class PathControllerCommon;
class SpellCastInfo;
class InventoryItem;
class SpellSlot;
class SpellData;
class Console;
class CallbackManager;
class DrawManager;
class GameClock;
class NetClient;
class Hud;
class Cursor;
class Input;
class Renderer;
class MenuManager;
class MenuTab;
class MenuItem;
class Chat;
class EntityList;
class NavMesh;
class ObjectManager;
class DamageLibManager;
class OrbwalkerManager;
class EvadeManager;
class TargetSelectorManager;
class HealthPredictionManager;
class PredictionManager;
class AntiGapcloserManager;
class Minimap;
class Scheduler;
class GlowManager;
class Spell;
class PermashowManager;

#define DEFINE_EXPORTED_CLASS(NAME) inline NAME* __exported##NAME = nullptr;
#define GET_EXPORTED_CLASS(NAME) virtual NAME* getExported##NAME () = 0;
#define CALL_EXPORTED_CLASS(NAME) __exported##NAME = getExported##NAME ();

#define SCRIPT_NAME(x) SCRIPT_EXPORT std::string script_name = x;
#define SCRIPT_TYPE(x) SCRIPT_EXPORT ScriptType script_type = x;
#define SUPPORTED_CHAMPS(...) SCRIPT_EXPORT std::vector<CharacterHash> script_champions = { __VA_ARGS__ };

DEFINE_EXPORTED_CLASS(MissileClient);
DEFINE_EXPORTED_CLASS(GameObject);
DEFINE_EXPORTED_CLASS(Buff);
DEFINE_EXPORTED_CLASS(PathControllerCommon);
DEFINE_EXPORTED_CLASS(SpellCastInfo);
DEFINE_EXPORTED_CLASS(InventoryItem);
DEFINE_EXPORTED_CLASS(SpellSlot);
DEFINE_EXPORTED_CLASS(SpellData);
DEFINE_EXPORTED_CLASS(Hud);
DEFINE_EXPORTED_CLASS(Cursor);
DEFINE_EXPORTED_CLASS(NetClient);
DEFINE_EXPORTED_CLASS(NavMesh);
DEFINE_EXPORTED_CLASS(ObjectManager);
DEFINE_EXPORTED_CLASS(Minimap);

inline SDK* sdk = nullptr;
inline GameObject* local_player = nullptr;
inline Console* console = nullptr;
inline CallbackManager* cb_manager = nullptr;
inline DrawManager* draw_manager = nullptr;
inline GameClock* game_time = nullptr;
inline Input* input = nullptr;
inline Renderer* renderer = nullptr;
inline MenuManager* menu_manager = nullptr;
inline Chat* chat = nullptr;
inline EntityList* entities = nullptr;
inline Hud* hud = nullptr;
inline Minimap* minimap = nullptr;
inline Cursor* cursor = nullptr;
inline NetClient* net_client = nullptr;
inline NavMesh* nav_mesh = nullptr;
inline ObjectManager* obj_manager = nullptr;
inline DamageLibManager* dmg_lib = nullptr;
inline OrbwalkerManager* orbwalker = nullptr;
inline EvadeManager* evade = nullptr;
inline TargetSelectorManager* target_selector = nullptr;
inline HealthPredictionManager* health_pred = nullptr;
inline PredictionManager* prediction = nullptr;
inline AntiGapcloserManager* anti_gapcloser = nullptr;
inline Scheduler* scheduler = nullptr;
inline GlowManager* glow = nullptr;
inline PermashowManager* permashow_manager = nullptr;

class SDK
{
public:
	GET_EXPORTED_CLASS(MissileClient);
	GET_EXPORTED_CLASS(GameObject);
	GET_EXPORTED_CLASS(Buff);
	GET_EXPORTED_CLASS(PathControllerCommon);
	GET_EXPORTED_CLASS(SpellCastInfo);
	GET_EXPORTED_CLASS(InventoryItem);
	GET_EXPORTED_CLASS(SpellSlot);
	GET_EXPORTED_CLASS(SpellData);
	GET_EXPORTED_CLASS(Hud);
	GET_EXPORTED_CLASS(Cursor);
	GET_EXPORTED_CLASS(NetClient);
	GET_EXPORTED_CLASS(NavMesh);
	GET_EXPORTED_CLASS(ObjectManager);
	virtual GameObject* get_local_player() = 0;
	virtual Console* get_console() = 0;
	virtual CallbackManager* get_cb_manager() = 0;
	virtual DrawManager* get_draw_manager() = 0;
	virtual GameClock* get_game_clock() = 0;
	virtual NetClient* get_net_client() = 0;
	virtual Hud* get_hud() = 0;
	virtual Minimap* get_minimap() = 0;
	virtual Cursor* get_cursor() = 0;
	virtual Input* get_input() = 0;
	virtual Renderer* get_renderer() = 0;
	virtual MenuManager* get_menu_manager() = 0;
	virtual Chat* get_chat() = 0;
	virtual EntityList* get_entity_list() = 0;
	virtual NavMesh* get_nav_mesh() = 0;
	virtual ObjectManager* get_object_manager() = 0;
	virtual DamageLibManager* get_damage_lib_manager() = 0;
	virtual OrbwalkerManager* get_orbwalker_manager() = 0;
	virtual EvadeManager* get_evade_manager() = 0;
	virtual TargetSelectorManager* get_target_selector_manager() = 0;
	virtual HealthPredictionManager* get_health_prediction_manager() = 0;
	virtual PredictionManager* get_prediction_manager() = 0;
	virtual AntiGapcloserManager* get_anti_gapcloser_manager() = 0;
	virtual Scheduler* get_scheduler() = 0;
	virtual GlowManager* get_glow_manager() = 0;
	virtual PermashowManager* get_permashow_manager() = 0;

	Spell* register_spell(SlotId slot, float range, DamageType damage_type = DamageType::Raw);
	bool remove_spell(Spell* spell);

	bool initialize()
	{
		sdk = this;

		CALL_EXPORTED_CLASS(MissileClient);
		CALL_EXPORTED_CLASS(GameObject);
		CALL_EXPORTED_CLASS(Buff);
		CALL_EXPORTED_CLASS(PathControllerCommon);
		CALL_EXPORTED_CLASS(SpellCastInfo);
		CALL_EXPORTED_CLASS(InventoryItem);
		CALL_EXPORTED_CLASS(SpellSlot);
		CALL_EXPORTED_CLASS(SpellData);
		CALL_EXPORTED_CLASS(NetClient);
		CALL_EXPORTED_CLASS(Hud);
		CALL_EXPORTED_CLASS(Cursor);
		CALL_EXPORTED_CLASS(NavMesh);
		CALL_EXPORTED_CLASS(ObjectManager);
		hud = get_hud();
		minimap = get_minimap();
		cursor = get_cursor();
		net_client = get_net_client();
		local_player = get_local_player();
		console = get_console();
		cb_manager = get_cb_manager();
		draw_manager = get_draw_manager();
		game_time = get_game_clock();
		input = get_input();
		renderer = get_renderer();
		menu_manager = get_menu_manager();
		chat = get_chat();
		entities = get_entity_list();
		nav_mesh = get_nav_mesh();
		obj_manager = get_object_manager();
		dmg_lib = get_damage_lib_manager();
		orbwalker = get_orbwalker_manager();
		evade = get_evade_manager();
		target_selector = get_target_selector_manager();
		health_pred = get_health_prediction_manager();
		prediction = get_prediction_manager();
		anti_gapcloser = get_anti_gapcloser_manager();
		scheduler = get_scheduler();
		glow = get_glow_manager();
		permashow_manager = get_permashow_manager();

		return true;
	}
};

struct NavCell
{
	uint16_t x;
	uint16_t y;
};

#define IMPORT_FUNC(RET, NAME, IN_ARGS, OUT_ARGS, CALL) \
	virtual __forceinline RET __EXPORTED##NAME IN_ARGS = 0; \
	RET NAME OUT_ARGS{ return FOCUS_CLASS->__EXPORTED##NAME CALL; };

#define FOCUS_CLASS __exportedPathControllerCommon
class PathControllerCommon
{
public:
	IMPORT_FUNC(bool, is_moving, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(bool, is_dashing, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(float, dash_speed, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_server_pos, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(std::vector<Vec3>, build_navigation_path, (PathControllerCommon* obj, const Vec3& from, const Vec3& to, bool smooth), (const Vec3& from, const Vec3& to, bool smooth = true), (this, from, to, smooth));
	IMPORT_FUNC(std::vector<Vec3>, get_path, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(std::vector<Vec2>, get_path_2d, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(int, get_curr_segment, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_nav_start, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_nav_end, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(int, get_nb_waypoints, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(float, get_path_length, (PathControllerCommon* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedGameObject
class GameObject
{
public:
	IMPORT_FUNC(void, issue_order, (GameObject* obj, IssueOrderType order, Vec3 position, GameObject* target), (IssueOrderType order, Vec3 position, GameObject* target), (this, order, position, target))
	IMPORT_FUNC(void, cast_spell, (GameObject* obj, SlotId slot_id, const Vec3& start_pos, const Vec3& end_pos, GameObject* target), (SlotId slot_id, const Vec3& start_pos, const Vec3& end_pos, GameObject* target), (this, slot_id, start_pos, end_pos, target))
	IMPORT_FUNC(void, update_charged_spell, (GameObject* obj, SlotId slot_id, const Vec3& position, bool release), (SlotId slot_id, const Vec3& position, bool release), (this, slot_id, position, release))
	IMPORT_FUNC(GameObjectType, get_type, (GameObject* obj), (), (this));
	IMPORT_FUNC(MissileClient*, get_missile_client, (GameObject* obj), (), (this));
	IMPORT_FUNC(PathControllerCommon*, get_path_controller_common, (GameObject* obj), (), (this));
	IMPORT_FUNC(SpellData*, get_basic_attack, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, has_item, (GameObject* obj, ItemId item_id), (ItemId item_id), (this, item_id));
	IMPORT_FUNC(bool, can_use_item, (GameObject* obj, ItemId item_id), (ItemId item_id), (this, item_id));
	IMPORT_FUNC(InventoryItem*, get_item, (GameObject* obj, ItemId item), (ItemId item), (this, item));
	IMPORT_FUNC(SpellSlot*, get_item_spell_slot, (GameObject* obj, ItemId item), (ItemId item), (this, item));

	// EffectEmitter
	IMPORT_FUNC(bool, is_effect_emitter, (GameObject* obj), (), (this));
	IMPORT_FUNC(uint32_t, get_effect_hash, (GameObject* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_emitter, (GameObject* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_attachment, (GameObject* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_target_attachment, (GameObject* obj), (), (this));
	// -----
	
	IMPORT_FUNC(SpellSlot*, get_spell, (GameObject* obj, SlotId id), (SlotId id), (this, id));
	IMPORT_FUNC(SpellCastInfo*, get_active_spell, (GameObject* obj), (), (this));
	IMPORT_FUNC(SpellState, get_spell_state, (GameObject* obj, SlotId slot_id), (SlotId slot_id), (this, slot_id));
	IMPORT_FUNC(bool, can_use_spell, (GameObject* obj, SlotId slot_id), (SlotId slot_id), (this, slot_id));
	IMPORT_FUNC(Buff*, get_buff, (GameObject* obj, const uint32_t hash), (const uint32_t hash), (this, hash));
	IMPORT_FUNC(bool, is_winding_up, (GameObject* obj), (), (this));

	IMPORT_FUNC(std::vector<Buff*>, get_buffs, (GameObject* obj), (), (this));
	IMPORT_FUNC(std::vector<Buff*>, get_buffs, (GameObject* obj, BuffType buffs_type), (BuffType buffs_type), (this, buffs_type));
	IMPORT_FUNC(std::vector<InventoryItem*>, get_items, (GameObject* obj), (), (this));

	IMPORT_FUNC(std::string, get_name, (GameObject* obj), (), (this));
	IMPORT_FUNC(std::string, get_model_name, (GameObject* obj), (), (this));
	IMPORT_FUNC(CharacterHash, get_character_hash, (GameObject* obj), (), (this));
	IMPORT_FUNC(Texture*, get_circle_icon, (GameObject* obj), (), (this));
	IMPORT_FUNC(Texture*, get_square_icon, (GameObject* obj), (), (this));

	IMPORT_FUNC(const Vec3&, get_position, (GameObject* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_direction, (GameObject* obj), (), (this));
	IMPORT_FUNC(Vec2, get_health_bar_screen_position, (GameObject* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_owner_player, (GameObject* obj), (), (this));

	IMPORT_FUNC(GameObjectTeam, get_team, (GameObject* obj), (), (this));

	IMPORT_FUNC(int, get_buff_count, (GameObject* obj, uint32_t buff_hash), (uint32_t buff_hash), (this, buff_hash));

	IMPORT_FUNC(unsigned, get_index, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, get_network_id, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_current_gold, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, get_visibility, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, get_level_up_points, (GameObject* obj), (), (this));
	IMPORT_FUNC(int, get_level, (GameObject* obj), (), (this));

	IMPORT_FUNC(float, get_bounding_radius, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_health, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_max_health, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_health, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_mana, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_shield, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_physical_shield, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_magic_shield, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_mana, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_max_mana, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_ability_haste, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_lethality, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_armor, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_armor, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_spell_block, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_spell_block, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_base_ad, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_ad, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_movement_speed, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_crit_damage_multiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_crit, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_ap, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_bonus_ap_multiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_attack_speed_multiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_real_attack_range, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_targetable, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_accumulated_experience, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_magic_pen_flat, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_armor_pen_multiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_magic_pen_multiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_mana_regen, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_health_regen, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_attack_delay, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_attack_cast_delay, (GameObject* obj), (), (this));

	IMPORT_FUNC(bool, is_invulnerable, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_visible_on_screen, (GameObject* obj, int tolerance = 0), (int tolerance = 0), (this, tolerance));
	IMPORT_FUNC(bool, is_melee, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_ranged, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_ally, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_ally, (GameObject* obj, GameObject* other), (GameObject* other), (this, other));
	IMPORT_FUNC(bool, is_enemy, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_enemy, (GameObject* obj, GameObject* other), (GameObject* other), (this, other));
	IMPORT_FUNC(bool, is_neutral, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_visible, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_zombie, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_recalling, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_teleporting, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, compare_object_type_flag, (GameObject* obj, TypeFlag flag), (TypeFlag flag), (this, flag));
	IMPORT_FUNC(bool, has_buff, (GameObject* obj, const uint32_t hash), (const uint32_t hash), (this, hash));
	IMPORT_FUNC(bool, has_buff_type, (GameObject* obj, BuffType buff_type), (BuffType buff_type), (this, buff_type));
	IMPORT_FUNC(bool, is_me, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_minion, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_lane_minion, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_inhibitor, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_nexus, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_hero, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_turret, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_missile, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_neutral_camp, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_ward, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_baron, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_herald, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_dragon, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_alive, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_plant, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_pet, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_practice_tool_dummy, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_clone, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, is_facing, (GameObject* obj, const Vec3& position), (const Vec3& position), (this, position));
	IMPORT_FUNC(bool, is_facing_obj, (GameObject* obj, GameObject* game_object), (GameObject* game_object), (this, game_object));
	IMPORT_FUNC(bool, is_in_range, (GameObject* obj, GameObject* game_object, float range), (GameObject* game_object, float range), (this, game_object, range));
	IMPORT_FUNC(bool, is_in_range_obj, (GameObject* obj, const Vec3& position, float range), (const Vec3& position, float range), (this, position, range));
	IMPORT_FUNC(bool, is_in_auto_attack_range, (GameObject* obj, GameObject* to, float extra_range = 0), (GameObject* to, float extra_range = 0), (this, to, extra_range));

	// !invulnerable, targetable, in_range, visible, alive
	IMPORT_FUNC(bool, is_valid_target, (GameObject* obj, float range, const Vec3& from = Vec3(), bool ignore_invulnerability = false), (float range = FLT_MAX, const Vec3& from = Vec3(), bool ignore_invulnerability = false), (this, range, from, ignore_invulnerability));

	IMPORT_FUNC(TurretType, get_turret_type, (GameObject* obj), (), (this));

	IMPORT_FUNC(float, get_total_respawn_time, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_remaining_respawn_time, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_gold_given_on_death, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, get_camp_respawn_time, (GameObject* obj), (), (this));

	__forceinline void cast_spell(SlotId slot) { cast_spell(slot, get_position(), get_position(), nullptr); }
	__forceinline void cast_spell(SlotId slot, GameObject* target) { cast_spell(slot, get_position(), target->get_position(), target); }
	__forceinline void cast_spell(SlotId slot, const Vec3& pos) { cast_spell(slot, get_position(), pos, nullptr); }

	__forceinline float get_health_percent() { return (get_health() / get_max_health()) * 100.f; }
	__forceinline float get_total_ad() { return get_base_ad() + get_bonus_ad(); }
	__forceinline float get_attack_range() { return get_bounding_radius() + get_real_attack_range(); }

	__forceinline std::vector<Vec3> build_navigation_path(const Vec3& start, const Vec3& end, bool smooth = true) { return get_path_controller_common()->build_navigation_path(start, end, smooth); }
	__forceinline Vec3 get_server_position() { return get_path_controller_common()->get_server_pos(); };


	__forceinline bool is_jungle_minion() { return is_minion() && is_neutral(); }
	bool is_super_minion();
	bool is_siege_minion();

	int count_enemies_in_range(float range);
	int count_allies_in_range(float range);

	bool is_under_enemy_turret();
	bool is_under_ally_turret();

	float get_distance(GameObject* other, bool use_height = false);
	float get_distance(const Vec3& pos, bool use_height = false);
	
	void move_to(const Vec3& pos);
	void attack(GameObject* obj);
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedObjectManager
class ObjectManager
{
public:
	IMPORT_FUNC(GameObject*, get_object_by_network_id, (ObjectManager* obj, unsigned network_id), (unsigned network_id), (this, network_id));
	IMPORT_FUNC(GameObject*, find_object, (ObjectManager* obj, unsigned id), (unsigned id), (this, id));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedMissileClient
class MissileClient
{
public:
	IMPORT_FUNC(SpellData*, get_spell_data, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_start_position, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_end_position, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_cast_position, (MissileClient* obj), (), (this));
	IMPORT_FUNC(SlotId, get_slot, (MissileClient* obj), (), (this));
	IMPORT_FUNC(unsigned, get_missile_index, (MissileClient* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_source, (MissileClient* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_target, (MissileClient* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellSlot
class SpellSlot
{
public:
	IMPORT_FUNC(SpellData*, get_spell_data, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(SlotId, get_slot_id, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(int, get_ammo, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_max_cooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(int, get_level, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_ready_at, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_damage, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_cooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_ammo_ready_at, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, get_ammo_cooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(Texture*, get_icon, (SpellSlot* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellData
class SpellData
{
public:
	IMPORT_FUNC(std::string, get_spell_name, (SpellData* obj), (), (this));
	IMPORT_FUNC(uint32_t, get_hash, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<std::string>, mSpellTags, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, mDataValues_BaseDamage, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, cooldown_time, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, delayCastOffsetPercent, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, delayTotalTimePercent, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<int>, mMaxAmmo, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, mAmmoRechargeTime, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, mTurnSpeedScalar, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, castRange, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, castRangeDisplayOverride, (SpellData* obj), (), (this));
	IMPORT_FUNC(std::vector<float>, castRadius, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, castConeDistance, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, mMissileSpec_mMissileWidth, (SpellData* obj), (), (this));
	IMPORT_FUNC(int, castType, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, castFrame, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, missileSpeed, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, mLineWidth, (SpellData* obj), (), (this));

	bool is_auto_reset();
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedInventoryItem
class InventoryItem
{
public:
	IMPORT_FUNC(int16_t, get_stacks, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(ItemId, get_item_id, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_price, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_ability_haste, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_health, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_movement_speed, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_armor, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_spell_block, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_ad, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_ap, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_attack_speed_multiplier, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(float, get_shield_power_multiplier, (InventoryItem* obj), (), (this));
	IMPORT_FUNC(ItemTexture, get_icon, (InventoryItem* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellCastInfo
class SpellCastInfo
{
public:
	IMPORT_FUNC(GameObject*, get_source, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_target, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(SpellData*, get_spell_data, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_start_pos, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_end_pos, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_cast_pos, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(bool, is_auto, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(bool, is_spell, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(bool, is_special_attack, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(SlotId, get_slot, (SpellCastInfo* obj), (), (this));
	IMPORT_FUNC(float, get_cast_delay, (SpellCastInfo* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedBuff
class Buff
{
public:
	IMPORT_FUNC(BuffType, get_type, (Buff* obj), (), (this));
	IMPORT_FUNC(int, get_count, (Buff* obj), (), (this));
	IMPORT_FUNC(float, get_start_time, (Buff* obj), (), (this));
	IMPORT_FUNC(float, get_end_time, (Buff* obj), (), (this));
	IMPORT_FUNC(float, get_remaining_time, (Buff* obj), (), (this));
	IMPORT_FUNC(float, get_total_duration, (Buff* obj), (), (this));
	IMPORT_FUNC(std::string, get_name, (Buff* obj), (), (this));
	IMPORT_FUNC(uint32_t, get_hash, (Buff* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_caster, (Buff* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_owner, (Buff* obj), (), (this));
	IMPORT_FUNC(Texture*, get_icon, (Buff* obj), (), (this));

	__forceinline bool is_active() { return get_remaining_time() > 0.f; }
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedNavMesh
class NavMesh
{
public:
	IMPORT_FUNC(float, get_height_for_position, (NavMesh* obj, const Vec3& pos), (const Vec3& pos), (this, pos));
	IMPORT_FUNC(CellFlags, get_pos_flags, (NavMesh* obj, const Vec3& pos), (const Vec3& pos), (this, pos));
	IMPORT_FUNC(uint8_t, get_cell_flags, (NavMesh* obj, const NavCell& cell), (const NavCell& cell), (this, cell));
	IMPORT_FUNC(bool, is_in_fow, (NavMesh* obj, const Vec3& pos), (const Vec3& pos), (this, pos));
	IMPORT_FUNC(void, set_pos_flags, (NavMesh* obj, const Vec3& pos, uint16_t flag), (const Vec3& pos, uint16_t flag), (this, pos, flag));
	IMPORT_FUNC(void, set_cell_flags, (NavMesh* obj, const NavCell& cell, uint16_t flag), (const NavCell& cell, uint16_t flag), (this, cell, flag));
	IMPORT_FUNC(NavCell, get_nav_cell, (NavMesh* obj, const Vec3& pos), (const Vec3& pos), (this, pos))
	IMPORT_FUNC(Vec3, get_cell_center, (NavMesh* obj, const NavCell& cell), (const NavCell& cell), (this, cell))
	IMPORT_FUNC(int, get_cell_count_x, (NavMesh* obj), (), (this))
	IMPORT_FUNC(int, get_cell_count_y, (NavMesh* obj), (), (this))
};
#undef FOCUS_CLASS
class Console
{
private:
	virtual void __log(const std::string& msg) = 0;
	virtual void __dbg(const std::string& msg) = 0;
	virtual void __err(const std::string& msg) = 0;
	virtual void __warn(const std::string& msg) = 0;
	virtual void __info(const std::string& msg) = 0;
public:

	void log(const char* msg, ...);
	void dbg(const char* msg, ...);
	void err(const char* msg, ...);
	void warn(const char* msg, ...);
	void info(const char* msg, ...);
};

class CallbackManager
{
public:
	virtual void add_callback(EventType cb_type, void* fct, const char* name) = 0;
	virtual bool remove_callback(EventType cb_type, void* fct) = 0;

	virtual bool fire_on_before_attack(GameObject* target) = 0;
	virtual void fire_on_after_attack(GameObject* target) = 0;

	virtual bool fire_on_before_move(Vec3* pos) = 0;
	virtual void fire_on_after_move(const Vec3& pos) = 0;
};

class Scheduler
{
public:
	virtual void delay_action(int delay_ticks, const std::function<void()> fn) = 0;
};

class DrawManager
{
public:
	virtual void screen_rectangle(const Vec2& p1, const Vec2& p2, uint32_t col, float rounding = 0.f, float thickness = 1.f, bool filled = false) = 0;
	virtual void rectangle_2points(const Vec3& start, const Vec3& end, uint32_t color, const int width, const float rounding = 0.f, const float thickness = 0.f) = 0;
	virtual void rectangle_4points(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, uint32_t color, const float thickness = 1.f) = 0;
	virtual void line(const Vec3& p1, const Vec3& p2, uint32_t col, float thickness = 1.f) = 0;
	virtual void screen_line(const Vec2& p1, const Vec2& p2, uint32_t col, float thickness = 1.f) = 0;
	virtual void screen_text(const Vec2& pos, const std::string& text, uint32_t color, int font_size) = 0;
	virtual void text(const Vec3& pos, const std::string& text, uint32_t color, int font_size) = 0;
	virtual void texture(const char* texture_path, const Vec2& pos, const Vec2& size, float rounding = 0, const uint32_t color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1)) = 0;
	virtual void texture(std::uint32_t texture_hash, const Vec2& pos, const Vec2& size, float rounding = 0, const uint32_t color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1)) = 0;
	virtual void texture(Texture* texture_ptr, const Vec2& pos, const Vec2& size, float rounding = 0, const uint32_t color = 0xFFFFFFFF, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1)) = 0;
	virtual void screen_circle(const Vec2& center, const float radius, uint32_t color, const float thickness = 1.f, const bool filled = false, const int num_points = 99) = 0;
	virtual void screen_circle_minimap(const Vec2& center, const float radius, uint32_t color, const float thickness = 1.f, const int num_points = 99) = 0;
	virtual void circle(const Vec3& center, const float radius, uint32_t color, const float thickness = 1.f, bool filled = false, const int num_points = 99) = 0;
	virtual void screen_arc(const Vec2& center, const float radius, const float a1, const float a2, const uint32_t color, const float thickness = 1.f) = 0;
	virtual void arc(const Vec3& center, const float radius, const float a1, const float a2, const uint32_t color, const float thickness = 1.f) = 0;
	virtual Vec2 calc_text_size(const std::string& text, int font_size) = 0;
};

class GameClock
{
public:
	virtual float	get_time() = 0;
	virtual int		get_tick_count() = 0;
};

class Minimap
{
public:
	virtual Vec2 get_size();
	virtual Vec2 get_position();
};

#define FOCUS_CLASS __exportedNetClient
class NetClient
{
public:
	IMPORT_FUNC(int, get_ping, (NetClient* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedHud
class Hud
{
public:
	IMPORT_FUNC(bool, is_window_focused, (Hud* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedCursor
class Cursor
{
public:
	IMPORT_FUNC(const Vec3&, get_world_position, (Cursor* obj), (), (this));
	IMPORT_FUNC(const Vec3&, get_last_click_position, (Cursor* obj), (), (this));
	IMPORT_FUNC(GameObject*, get_hovered_unit, (Cursor* obj), (), (this));
};
#undef FOCUS_CLASS
class Input
{
public:
	virtual bool is_key_down(uint32_t key) = 0;
	virtual bool is_key_up(uint32_t key) = 0;
	virtual bool is_key_pressed(uint32_t key) = 0;
	virtual Vec2 get_cursor_screen_position() = 0;
};

class Renderer
{
public:
	virtual Vec2 get_renderer_size() = 0;
	virtual Vec2 world_to_screen(const Vec3& in) = 0;
	virtual Vec2 world_to_minimap(const Vec3& in) = 0;
	virtual Texture* get_texture_from_game(const std::string& texture_name) = 0;
};

class MenuManager
{
public:
	virtual MenuTab* create_menu(const std::string& key, const std::string& name, const std::string& icon = ICON_FA_BARS) = 0;
	virtual bool delete_menu(MenuTab* menu) = 0;
	virtual bool delete_menu(const std::string& key) = 0;

	virtual MenuTab* get_menu(const std::string& key) = 0;
	virtual std::vector<MenuTab*> get_menus() = 0;
};

class MenuParent
{
public:
	virtual void			__DONTCALL1() = 0;
	virtual void			__DONTCALL2() = 0;
	virtual void			__DONTCALL3() = 0;
	virtual void			__DONTCALL4() = 0;
	virtual void			__DONTCALL5() = 0;
	virtual void			__DONTCALL6() = 0;
	virtual void			__DONTCALL7() = 0;
	virtual void			__DONTCALL8() = 0;
	virtual void			__DONTCALL9() = 0;
};

class MenuItem : public MenuParent
{
public:
	virtual const std::string&		get_key() = 0;
	virtual const std::string&		get_name() = 0;

	virtual bool			get_bool() = 0;
	virtual int				get_int() = 0;
	virtual uint32_t		get_color() = 0;

	virtual void			set_bool(bool b) = 0;
	virtual void			set_int(int i) = 0;
	virtual void			set_color(uint32_t col) = 0;

	virtual void			set_visibility(bool* vis) = 0;
	virtual void			set_visibility(MenuItem* entry) = 0;

	virtual void			set_on_update(const std::function<void()>& on_update) = 0;
	virtual void			set_on_value_change(const std::function<void(MenuItem*)>& on_value_change) = 0;
	virtual void			set_tooltip(const std::string& tooltip) = 0;
	virtual void			set_texture(Texture* texture) = 0;
};

class MenuTab : public MenuParent
{
public:
	virtual const std::string& get_key() = 0;
	virtual const std::string& get_name() = 0;

	virtual MenuTab* add_menu(const std::string& key, const std::string& name, const std::string& icon = ICON_FA_BARS) = 0;
	virtual MenuItem* add_separator(const std::string& key, const std::string& name) = 0;
	virtual MenuItem* add_checkbox(const std::string& key, const std::string& name, bool value, const std::string& icon = ICON_FA_CHECK) = 0;
	virtual MenuItem* add_slider(const std::string& key, const std::string& name, int default_value, int min_value, int max_value, const std::string& icon = ICON_FA_ARROWS_ALT_H) = 0;
	virtual MenuItem* add_colorpick(const std::string& key, const std::string& name, uint32_t default_value, const std::string& icon = ICON_FA_PALETTE) = 0;
	virtual MenuItem* add_combo(const std::string& key, const std::string& name, int default_value, const std::vector<std::string>& values, const std::string& icon = ICON_FA_LIST) = 0;
	virtual MenuItem* add_keybind(const std::string& key, const std::string& name, bool hold, int default_key, bool default_value, const std::string& icon = ICON_FA_KEYBOARD) = 0;
	virtual MenuItem* add_button(const std::string& key, const std::string& name, const std::string& button_text, const std::function<void()>& func) = 0;

	virtual void set_texture(Texture* menu_texture) = 0;
	virtual void set_enabled(bool* enabled) = 0;
	virtual void set_enabled(MenuItem* item) = 0;

	virtual MenuItem* get_item(const std::string& key) = 0;

	virtual bool delete_item(MenuItem* item) = 0;
	virtual bool delete_item(const std::string& key) = 0;
};

class Chat
{
public:
	virtual void print(const std::string& message) = 0;
	virtual void send(const std::string& message, bool all_chat = false) = 0;
};

class EntityList
{
public:
	virtual std::vector<GameObject*> get_heroes() = 0;
	virtual std::vector<GameObject*> get_minions() = 0;

	virtual std::vector<GameObject*> get_turrets() = 0;
	virtual std::vector<GameObject*> get_ally_turrets() = 0;
	virtual std::vector<GameObject*> get_enemy_turrets() = 0;

	virtual std::vector<GameObject*> get_inhibitors() = 0;
	virtual std::vector<GameObject*> get_ally_inhibitors() = 0;
	virtual std::vector<GameObject*> get_enemy_inhibitors() = 0;

	virtual std::vector<GameObject*> get_nexus() = 0;
	virtual GameObject* get_ally_nexus() = 0;
	virtual GameObject* get_enemy_nexus() = 0;

	virtual std::vector<GameObject*> get_missiles() = 0;
	virtual std::vector<GameObject*> get_ally_missiles() = 0;
	virtual std::vector<GameObject*> get_enemy_missiles() = 0;

	virtual std::vector<GameObject*> get_clones() = 0;
	virtual std::vector<GameObject*> get_ally_clones() = 0;
	virtual std::vector<GameObject*> get_enemy_clones() = 0;

	virtual std::vector<GameObject*> get_neutral_camps() = 0;

	virtual std::vector<GameObject*> get_all_objects() = 0;
};

struct DamageOutput
{
	double magical;
	double physical;
	double raw;

	DamageOutput(double magical, double physical, double raw) : magical(magical), physical(physical), raw(raw) { }
	DamageOutput() : magical(0.0), physical(0.0), raw(0.0) { }

	DamageType get_damage_type() const
	{
		if (magical > 0.0 && physical > 0.0)
			return DamageType::Mixed;

		if (magical > 0.0)
			return DamageType::Magical;

		if (physical > 0.0)
			return DamageType::Physical;

		if (raw > 0.0)
			return DamageType::Raw;

		return DamageType::Physical;
	}

	operator double() const { return magical + physical + raw; }

	DamageOutput& operator +=(DamageOutput other)
	{
		magical += other.magical;
		physical += other.physical;
		raw += other.raw;

		return *this;
	}

	DamageOutput& operator -=(DamageOutput other)
	{
		magical -= other.magical;
		physical -= other.physical;
		raw -= other.raw;

		return *this;
	}
};

class DamageLibManager
{
	typedef DamageOutput(*fn_get_spell_damage)(GameObject*, GameObject*, SlotId, int stage, int stacks);
	typedef double(*fn_calculate_damage)(GameObject*, GameObject*, DamageType, double);
	typedef DamageOutput(*fn_get_auto_attack_damage)(GameObject*, GameObject*, bool, bool);
public:
	virtual void set_callbacks(
		fn_get_spell_damage get_spell_damage,
		fn_calculate_damage calculate_damage,
		fn_get_auto_attack_damage get_auto_attack_damage
	) = 0;

	virtual DamageOutput get_spell_damage(GameObject* source, GameObject* target, SlotId spell_slot, int stage = 1, int stacks = 1) = 0;
	virtual double calculate_damage(GameObject* source, GameObject* target, DamageType damage_Type, double base_damage) = 0;
	virtual DamageOutput get_auto_attack_damage(GameObject* source, GameObject* target, bool include_passives = true, bool include_items = true) = 0;
};

class OrbwalkerManager
{
	typedef OrbwalkerMode(*fn_get_mode)();
public:
	virtual void set_callbacks(
		fn_get_mode get_mode
	) = 0;
	
	virtual OrbwalkerMode get_mode() = 0;
};

class EvadeManager
{
public:
};

class TargetSelectorManager
{
	typedef GameObject* (*fn_get_target)(float, DamageType, bool);
	typedef GameObject* (*fn_get_target2)(const std::vector<GameObject*>&, DamageType);
	typedef GameObject* (*fn_get_selected_target)();
	typedef void (*fn_set_selected_target)(GameObject*);
public:
	virtual void set_callbacks(
		fn_get_target get_target,
		fn_get_target2 get_target2,
		fn_get_selected_target get_selected_target,
		fn_set_selected_target set_selected_target
	) = 0;

	virtual GameObject* get_target(float range, DamageType damage_type, bool ignore_invulnerability = false) = 0;
	virtual GameObject* get_target(const std::vector<GameObject*>& objects, DamageType damage_type) = 0;
	virtual GameObject* get_selected_target() = 0;
	virtual void set_selected_target(GameObject* target) = 0;
};

class HealthPredictionManager
{
	typedef float(*fn_get_health_prediction)(GameObject*, int, int);
	typedef float(*fn_get_incoming_damage)(GameObject*, int, int);
	typedef bool(*fn_has_turret_aggro)(GameObject*);
	typedef bool(*fn_has_minion_aggro)(GameObject*);
	typedef int(*fn_turret_aggro_start_time)(GameObject*);
	typedef GameObject* (*fn_get_aggro_turret)(GameObject*);
public:
	virtual void set_callbacks(
		fn_get_health_prediction get_health_prediction,
		fn_get_incoming_damage get_incoming_damage,
		fn_has_turret_aggro has_turret_aggro,
		fn_has_minion_aggro has_minion_aggro,
		fn_turret_aggro_start_time turret_aggro_start_time,
		fn_get_aggro_turret get_aggro_turret
	) = 0;

	virtual float get_health_prediction(GameObject* obj, int time, int delay = 70) = 0;
	virtual float get_incoming_damage(GameObject* obj, int time, int delay = 70) = 0;
	virtual bool has_turret_aggro(GameObject* minion) = 0;
	virtual bool has_minion_aggro(GameObject* minion) = 0;
	virtual int turret_aggro_start_time(GameObject* minion) = 0;
	virtual GameObject* get_aggro_turret(GameObject* minion) = 0;
};

struct PredictionInput
{
    Vec3 _from;
    Vec3 _range_check_from;
    bool add_bounding = true;
    bool aoe;
	bool collision = true;
    std::vector<CollisionObject> collision_objects { };
    float delay = 0.f;
    float radius = 1.f;
    float range = FLT_MAX;
    float speed = FLT_MAX;
    SkillshotType type = SkillshotType::Line;
    SlotId spell_slot = SlotId::Unknown;
    GameObject* unit = local_player;

    Vec3 from() const
    {
    	return !_from.is_valid() ? local_player->get_server_position() : _from;
    };
	
    Vec3 range_check_from() const
    {
	    if (_range_check_from.is_valid())
	    	return _range_check_from;

    	return !from().is_valid() ? local_player->get_server_position() : from();
    }
	
    float real_radius() const
    {
	    return !add_bounding ? radius : radius + unit->get_bounding_radius();
    }
};

struct PredictionOutput
{
	PredictionInput* input;

	Vec3 _cast_position;
	Vec3 _unit_position;
	
	std::vector<GameObject*> collision_objects;
	HitChance hit_chance = HitChance::Impossible;
	std::vector<GameObject*> aoe_targets_hit;
	int _aoe_targets_hit_count = 0;
	
	int aoe_targets_hit_count() const
	{
		return std::max(_aoe_targets_hit_count, (int) aoe_targets_hit.size());
	}
	
	Vec3 cast_position() const
	{
		if (_cast_position.is_valid())
			return _cast_position;
		
		if (input == nullptr)
			return Vec3();
		
		return input->unit != nullptr ? input->unit->get_server_position() : Vec3();
	}
	
	Vec3 unit_position() const
	{
		if (_unit_position.is_valid())
			return _unit_position;
		
		if (input == nullptr)
			return Vec3();
		
		return input->unit != nullptr ? input->unit->get_server_position() : Vec3();
	}
};

class PredictionManager
{
	typedef PredictionOutput(*fn_get_prediction)(PredictionInput*);
public:
	virtual void set_callbacks(
		fn_get_prediction get_prediction
	) = 0;

	virtual PredictionOutput get_prediction(PredictionInput* input) = 0;
};

struct GapCloserInformation
{
	GapCloserType type = GapCloserType::Skillshot;
	GameObject* sender = nullptr;
	GameObject* target = nullptr;

	float start_time = 0.f;
	float end_time = 0.f;
	float speed = 0.f;

	Vec3 start_position { };
	Vec3 end_position { };

	bool is_unstoppable = false;
	bool is_cc = false;
};

typedef void(*gapcloser_event)(GapCloserInformation* gap_closer);
class AntiGapcloserManager
{
	typedef GapCloserInformation(*fn_get_gapcloser_information)(GameObject*, bool);
	typedef bool(*fn_add_callback)(gapcloser_event);
public:
	virtual void set_callbacks(
		fn_get_gapcloser_information get_gapcloser_information,
		fn_add_callback add_callback
	) = 0;

	virtual GapCloserInformation get_gapcloser_information(GameObject* obj, bool all_dash = false) = 0;
	virtual bool add_callback(gapcloser_event callback) = 0;
};

class GlowManager
{
public:
	virtual bool register_object(GameObject* obj, uint32_t color, int glow_size, int glow_blur) = 0;
	virtual bool remove_object(GameObject* obj) = 0;
	virtual bool is_glowing(GameObject* obj) = 0;
};

class Spell
{
public:
	Spell() : _range(FLT_MAX) { }
	Spell(SlotId slot) : slot(slot), _range(FLT_MAX) { }
	Spell(SlotId slot, float range) : slot(slot), _range(range) { }
	Spell(SlotId slot, float range, DamageType damage_type) : slot(slot), _range(range), _damage_type(damage_type) { }
	Spell(SlotId slot, float range, SkillshotType type, float delay, float speed, float radius, bool collision) :
		slot(slot),
		type(type),
		_range(range),
		_delay(delay),
		_speed(speed),
		_radius(radius),
		collision(collision),
		from(Vec3::zero),
		range_check_from(Vec3::zero)
	{ }

	const float cast_cooldown = .1f;
	float last_spell_cast { };

	bool lock_enabled = false;

	SlotId slot = SlotId::Unknown;
	SkillshotType type{ };
	float _range{ };
	float _delay{ };
	float _speed{ };
	float _radius { };
	bool collision = false;
	bool is_charged_spell = false;

	DamageType _damage_type = DamageType::Physical;

	std::vector<CollisionObject> collision_objects{ };
	
	Vec3 from { };
	Vec3 range_check_from { };
	DamageType damage_type{ };

	uint32_t charge_buff_hash { };
	float charging_started_time { };
	float charged_min_range { };
	float charged_max_range { };
	float charged_started_time { };
	float charge_duration { };

	SpellSlot* handle();

	Texture* texture();

	float cooldown_time();
	float range();

	int ammo();
	int level();

	bool is_ready(float time = 0.f);

	bool cast();
	bool cast(const Vec3& position);
	bool cast(GameObject* obj);

	Buff* get_charge_buff();
	float charged_percentage();
	bool is_charging();
	bool is_charged();

	void set_skillshot(float delay, float radius, float speed, const std::vector<CollisionObject>& collision_objects, SkillshotType type);
	void set_charged(float range_min, float range_max, float charge_duration);

	bool start_charging();
	bool start_charging(const Vec3& pos);

	GameObject* get_target(float extra_range = 0.f);

	PredictionOutput get_prediction(GameObject* target, bool aoe = false, const std::vector<CollisionObject>& collision = { }, float override_range = -1.f);
	PredictionOutput get_prediction(GameObject* target, const Vec3& origin, const Vec3& range_check_from);
	PredictionOutput get_prediction_no_collision(GameObject* target, bool aoe = false, float override_range = -1.f);

	bool is_locked();

	float get_damage(GameObject* target, int stage = 1, int stacks = 1);
};

class Permashow
{
public:
	virtual bool add_element(MenuItem* item, const std::string& custom_name = "") = 0;
	virtual bool add_element(const std::string& name, bool* item) = 0;
	virtual bool add_element(const std::string& name, std::string* item) = 0;

	virtual bool remove_element(MenuItem* item) = 0;
	virtual bool remove_element(const std::string& name) = 0;
	virtual void clear_elements() = 0;

	virtual void set_draw(MenuItem* item);
	virtual void set_draw(bool* b);

	virtual std::string get_name() = 0;
};

class PermashowManager
{
public:
	virtual Permashow* add_permashow(MenuTab* menu, const Vec2& position = { }) = 0;
	virtual Permashow* get_permashow(const std::string& name) = 0;

	virtual bool remove_permashow(Permashow* permashow) = 0;
};

template < EventType event >
struct callbacks
{
	static void add_callback() { }
	static void remove_callback() { }
};

template < >
struct callbacks<EventType::OnTick>
{
	static void add_callback(void(*callback)(), const char* name) { cb_manager->add_callback(EventType::OnTick, (void*)callback, name); }
	static void remove_callback(void(*callback)()) { cb_manager->remove_callback(EventType::OnTick, (void*)callback); }
};

template < >
struct callbacks<EventType::OnSlowTick>
{
	static void add_callback(void(*callback)(), const char* name) { cb_manager->add_callback(EventType::OnSlowTick, (void*)callback, name); }
	static void remove_callback(void(*callback)()) { cb_manager->remove_callback(EventType::OnSlowTick, (void*)callback); }
};

template < >
struct callbacks<EventType::OnDraw>
{
	static void add_callback(void(*callback)(), const char* name) { cb_manager->add_callback(EventType::OnDraw, (void*)callback, name); }
	static void remove_callback(void(*callback)()) { cb_manager->remove_callback(EventType::OnDraw, (void*)callback); }
};

template < >
struct callbacks<EventType::OnDrawEnvironment>
{
	static void add_callback(void(*callback)(), const char* name) { cb_manager->add_callback(EventType::OnDrawEnvironment, (void*)callback, name); }
	static void remove_callback(void(*callback)()) { cb_manager->remove_callback(EventType::OnDrawEnvironment, (void*)callback); }
};

template < >
struct callbacks<EventType::OnWndProc>
{
	static void add_callback(void(*callback)(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* execute), const char* name) { cb_manager->add_callback(EventType::OnWndProc, (void*)callback, name); }
	static void remove_callback(void(*callback)(HWND, UINT, WPARAM, LPARAM, bool*)) { cb_manager->remove_callback(EventType::OnWndProc, (void*)callback); }
};

template < >
struct callbacks<EventType::OnProcessSpellCast>
{
	static void add_callback(void(*callback)(SpellCastInfo* processed_spell), const char* name) { cb_manager->add_callback(EventType::OnProcessSpellCast, (void*)callback, name); }
	static void remove_callback(void(*callback)(SpellCastInfo*)) { cb_manager->remove_callback(EventType::OnProcessSpellCast, (void*)callback); }
};

template < >
struct callbacks<EventType::OnCreateObject>
{
	static void add_callback(void(*callback)(GameObject* obj), const char* name) { cb_manager->add_callback(EventType::OnCreateObject, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject*)) { cb_manager->remove_callback(EventType::OnCreateObject, (void*)callback); }
};

template < >
struct callbacks<EventType::OnDeleteObject>
{
	static void add_callback(void(*callback)(GameObject* obj), const char* name) { cb_manager->add_callback(EventType::OnDeleteObject, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject*)) { cb_manager->remove_callback(EventType::OnDeleteObject, (void*)callback); }
};

template < >
struct callbacks<EventType::OnStopCast>
{
	static void add_callback(void(*callback)(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled), const char* name) { cb_manager->add_callback(EventType::OnStopCast, (void*)callback, name); }
	static void remove_callback(void(*callback)(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled)) { cb_manager->remove_callback(EventType::OnStopCast, (void*)callback); }
};

template < >
struct callbacks<EventType::OnIssueOrder>
{
	static void add_callback(void(*callback)(IssueOrderType order, Vec3* position, GameObject* target, bool *process), const char* name) { cb_manager->add_callback(EventType::OnIssueOrder, (void*)callback, name); }
	static void remove_callback(void(*callback)(IssueOrderType order, Vec3* position, GameObject* target, bool* process)) { cb_manager->remove_callback(EventType::OnIssueOrder, (void*)callback); }
};

template < >
struct callbacks<EventType::OnCastSpell>
{
	static void add_callback(void(*callback)(SlotId slot_id, Vec3* start_position, Vec3* end_position, GameObject* target, bool* process), const char* name) { cb_manager->add_callback(EventType::OnCastSpell, (void*)callback, name); }
	static void remove_callback(void(*callback)(SlotId slot_id, Vec3* start_position, Vec3* end_position, GameObject* target, bool* process)) { cb_manager->remove_callback(EventType::OnCastSpell, (void*)callback); }
};

template < >
struct callbacks<EventType::OnCastComplete>
{
	static void add_callback(void(*callback)(SpellCastInfo* processed_spell), const char* name) { cb_manager->add_callback(EventType::OnCastComplete, (void*)callback, name); }
	static void remove_callback(void(*callback)(SpellCastInfo* processed_spell)) { cb_manager->remove_callback(EventType::OnCastComplete, (void*)callback); }
};

template < >
struct callbacks<EventType::OnSpellImpact>
{
	static void add_callback(void(*callback)(SpellCastInfo* processed_spell), const char* name) { cb_manager->add_callback(EventType::OnSpellImpact, (void*)callback, name); }
	static void remove_callback(void(*callback)(SpellCastInfo* processed_spell)) { cb_manager->remove_callback(EventType::OnSpellImpact, (void*)callback); }
};

template < >
struct callbacks<EventType::OnPlayAnimation>
{
	static void add_callback(void(*callback)(GameObject* sender, const std::string& animation_name, uint32_t animation_hash, bool* process), const char* name) { cb_manager->add_callback(EventType::OnPlayAnimation, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject* sender, const std::string& animation_name, uint32_t animation_hash, bool* process)) { cb_manager->remove_callback(EventType::OnPlayAnimation, (void*)callback); }
};

template < >
struct callbacks<EventType::OnBuffGainLose>
{
	static void add_callback(void(*callback)(Buff* buff, bool gain), const char* name) { cb_manager->add_callback(EventType::OnBuffGainLose, (void*)callback, name); }
	static void remove_callback(void(*callback)(Buff* buff, bool gain)) { cb_manager->remove_callback(EventType::OnBuffGainLose, (void*)callback); }
};

template < >
struct callbacks<EventType::OnSetPath>
{
	static void add_callback(void(*callback)(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed), const char* name) { cb_manager->add_callback(EventType::OnSetPath, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed)) { cb_manager->remove_callback(EventType::OnSetPath, (void*)callback); }
};

template < >
struct callbacks<EventType::OnProcessAutoAttack>
{
	static void add_callback(void(*callback)(GameObject* sender, SpellData* auto_attack), const char* name) { cb_manager->add_callback(EventType::OnProcessAutoAttack, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject* sender, SpellData* auto_attack)) { cb_manager->remove_callback(EventType::OnProcessAutoAttack, (void*)callback); }
};

template < >
struct callbacks<EventType::OnNotifyEvent>
{
	static void add_callback(void(*callback)(GameObject* source, const char* event_name, int event_id), const char* name) { cb_manager->add_callback(EventType::OnNotifyEvent, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject* source, const char* event_name, int event_id)) { cb_manager->remove_callback(EventType::OnNotifyEvent, (void*)callback); }
};

template < >
struct callbacks<EventType::OnBeforeAttackOrbwalker>
{
	static void add_callback(bool(*callback)(GameObject* target), const char* name) { cb_manager->add_callback(EventType::OnBeforeAttackOrbwalker, (void*)callback, name); }
	static void remove_callback(bool(*callback)(GameObject* target)) { cb_manager->remove_callback(EventType::OnBeforeAttackOrbwalker, (void*)callback); }
};

template < >
struct callbacks<EventType::OnAfterAttackOrbwalker>
{
	static void add_callback(void(*callback)(GameObject* target), const char* name) { cb_manager->add_callback(EventType::OnAfterAttackOrbwalker, (void*)callback, name); }
	static void remove_callback(void(*callback)(GameObject* target)) { cb_manager->remove_callback(EventType::OnAfterAttackOrbwalker, (void*)callback); }
};

template < >
struct callbacks<EventType::OnBeforeMoveOrbwalker>
{
	static void add_callback(bool(*callback)(Vec3* pos), const char* name) { cb_manager->add_callback(EventType::OnBeforeMoveOrbwalker, (void*)callback, name); }
	static void remove_callback(bool(*callback)(Vec3* pos)) { cb_manager->remove_callback(EventType::OnBeforeMoveOrbwalker, (void*)callback); }
};

template < >
struct callbacks<EventType::OnAfterMoveOrbwalker>
{
	static void add_callback(void(*callback)(const Vec3& pos), const char* name) { cb_manager->add_callback(EventType::OnAfterMoveOrbwalker, (void*)callback, name); }
	static void remove_callback(void(*callback)(const Vec3& pos)) { cb_manager->remove_callback(EventType::OnAfterMoveOrbwalker, (void*)callback); }
};

template<class C, class T>
auto vector_contains(const C& v, const T& x)
-> decltype(end(v), true)
{
	return end(v) != std::find(begin(v), end(v), x);
}

template<typename T>
class Singleton
{
protected:
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

public:
	static T& get()
	{
		static T inst{};
		return inst;
	}
};