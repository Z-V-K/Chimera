#include "DamageLib.h"

#include "Items/Botrk.h"
#include "Items/CeaselessHunger.h"
#include "Items/DeadMansPlate.h"
#include "Items/Deicide.h"
#include "Items/DivineSunderer.h"
#include "Items/DoransRing.h"
#include "Items/DoransShield.h"
#include "Items/DrakhtarrsShadowcarver.h"
#include "Items/DreamShatter.h"
#include "Items/DuskbladeOfDrakhtarr.h"
#include "Items/EssenceReaver.h"
#include "Items/EternalWinter.h"
#include "Items/Everfrost.h"
#include "Items/FrozenFist.h"
#include "Items/Galeforce.h"
#include "Items/Goredrinker.h"
#include "Items/GuinsooRageblade.h"
#include "Items/HextechRocketbelt.h"
#include "Items/IcebornGauntlet.h"
#include "Items/InfinityForce.h"
#include "Items/IronspikeWhip.h"
#include "Items/KircheisShard.h"
#include "Items/KrakenSlayer.h"
#include "Items/LichBane.h"
#include "Items/Muramana.h"
#include "Items/NashorsTooth.h"
#include "Items/Noonquiver.h"
#include "Items/ProwlersClaw.h"
#include "Items/Rageknife.h"
#include "Items/RapidFirecannon.h"
#include "Items/RecurveBow.h"
#include "Items/RunaanHurricane.h"
#include "Items/SeethingSorrow.h"
#include "Items/Sheen.h"
#include "Items/StatikkShiv.h"
#include "Items/Stormrazor.h"
#include "Items/StrideBreaker.h"
#include "Items/TearOfTheGoddess.h"
#include "Items/TitanicHydra.h"
#include "Items/TrinityForce.h"
#include "Items/Typhoon.h"
#include "Items/UpgradedAeropack.h"
#include "Items/WitsEnd.h"
#include "Passives/Champions/AatroxPassive.h"
#include "Passives/Champions/AkaliPassive.h"
#include "Passives/Champions/AkshanPassive.h"
#include "Passives/Champions/AlistarPassive.h"
#include "Passives/Champions/ApheliosPassive.h"
#include "Passives/Champions/AshePassive.h"
#include "Passives/Champions/BardPassive.h"
#include "Passives/Champions/BelvethPassive.h"
#include "Passives/Champions/BlitzcrankPassive.h"
#include "Passives/Champions/BraumMarkPassive.h"
#include "Passives/Champions/BraumPassive.h"
#include "Passives/Champions/CaitlynPassive.h"
#include "Passives/Champions/CamillePassive.h"
#include "Passives/Champions/ChogathPassive.h"
#include "Passives/Champions/CorkiPassive.h"
#include "Passives/Champions/DariusPassive.h"
#include "Passives/Champions/DianaPassive.h"
#include "Passives/Champions/DravenPassive.h"
#include "Passives/Champions/DrMundoPassive.h"
#include "Passives/Champions/EkkoPassive.h"
#include "Passives/Champions/ElisePassive.h"
#include "Passives/Champions/EzrealPassive.h"
#include "Passives/Champions/FioraPassive.h"
#include "Passives/Champions/FizzPassive.h"
#include "Passives/Champions/GalioPassive.h"
#include "Passives/Champions/GangplankPassive.h"
#include "Passives/Champions/GarenPassive.h"
#include "Passives/Champions/GnarPassive.h"
#include "Passives/Champions/GragasPassive.h"
#include "Passives/Champions/GwenPassive.h"
#include "Passives/Champions/HecarimPassive.h"
#include "Passives/Champions/IllaoiPassive.h"
#include "Passives/Champions/IreliaPassive.h"
#include "Passives/Champions/IvernPassive.h"
#include "Passives/Champions/JarvanPassive.h"
#include "Passives/Champions/JaxPassive.h"
#include "Passives/Champions/JaycePassive.h"
#include "Passives/Champions/JhinPassive.h"
#include "Passives/Champions/JinxPassive.h"
#include "Passives/Champions/KaisaPassive.h"
#include "Passives/Champions/KalistaMarkPassive.h"
#include "Passives/Champions/KalistaPassive.h"
#include "Passives/Champions/KassadinPassive.h"
#include "Passives/Champions/KaylePassive.h"
#include "Passives/Champions/KennenPassive.h"
#include "Passives/Champions/KhazixPassive.h"
#include "Passives/Champions/KledPassive.h"
#include "Passives/Champions/KogmawPassive.h"
#include "Passives/Champions/LeonaPassive.h"
#include "Passives/Champions/LucianPassive.h"
#include "Passives/Champions/LuxPassive.h"
#include "Passives/Champions/MalphitePassive.h"
#include "Passives/Champions/MasterYiPassive.h"
#include "Passives/Champions/MissFortunePassive.h"
#include "Passives/Champions/MonkeyKingPassive.h"
#include "Passives/Champions/NamiMarkPassive.h"
#include "Passives/Champions/NasusPassive.h"
#include "Passives/Champions/NautilusPassive.h"
#include "Passives/Champions/NeekoPassive.h"
#include "Passives/Champions/NidaleePassive.h"
#include "Passives/Champions/NocturnePassive.h"
#include "Passives/Champions/OriannaPassive.h"
#include "Passives/Champions/OrnnPassive.h"
#include "Passives/Champions/PoppyPassive.h"
#include "Passives/Champions/QiyanaPassive.h"
#include "Passives/Champions/QuinnPassive.h"
#include "Passives/Champions/RammusPassive.h"
#include "Passives/Champions/RekSaiPassive.h"
#include "Passives/Champions/RenataMarkPassive.h"
#include "Passives/Champions/RenataPassive.h"
#include "Passives/Champions/RenektonPassive.h"
#include "Passives/Champions/RengarPassive.h"
#include "Passives/Champions/RivenPassive.h"
#include "Passives/Champions/RumblePassive.h"
#include "Passives/Champions/SamiraPassive.h"
#include "Passives/Champions/SejuaniPassive.h"
#include "Passives/Champions/SettPassive.h"
#include "Passives/Champions/ShacoPassive.h"
#include "Passives/Champions/ShenPassive.h"
#include "Passives/Champions/ShyvanaPassive.h"
#include "Passives/Champions/SionPassive.h"
#include "Passives/Champions/SkarnerPassive.h"
#include "Passives/Champions/SonaMarkPassive.h"
#include "Passives/Champions/SonaPassive.h"
#include "Passives/Champions/SylasPassive.h"
#include "Passives/Champions/TahmKenchPassive.h"
#include "Passives/Champions/TalonPassive.h"
#include "Passives/Champions/TeemoPassive.h"
#include "Passives/Champions/ThreshPassive.h"
#include "Passives/Champions/TrundlePassive.h"
#include "Passives/Champions/TwistedFatePassive.h"
#include "Passives/Champions/UdyrPassive.h"
#include "Passives/Champions/UrgotPassive.h"
#include "Passives/Champions/VarusPassive.h"
#include "Passives/Champions/VaynePassive.h"
#include "Passives/Champions/VexPassive.h"
#include "Passives/Champions/ViPassive.h"
#include "Passives/Champions/VolibearPassive.h"
#include "Passives/Champions/WarwickPassive.h"
#include "Passives/Champions/XayahMarkPassive.h"
#include "Passives/Champions/XinZhaoPassive.h"
#include "Passives/Champions/YasuoPassive.h"
#include "Passives/Champions/YorickPassive.h"
#include "Passives/Champions/ZeriPassive.h"
#include "Passives/Champions/ZiggsPassive.h"
#include "Passives/Champions/ZoePassive.h"
#include "Spells/DamageChamp.h"
#include "Spells/Champions/Aatrox.h"
#include "Spells/Champions/Ahri.h"
#include "Spells/Champions/Akali.h"
#include "Spells/Champions/Akshan.h"
#include "Spells/Champions/Alistar.h"
#include "Spells/Champions/Amumu.h"
#include "Spells/Champions/Anivia.h"
#include "Spells/Champions/Annie.h"
#include "Spells/Champions/Aphelios.h"
#include "Spells/Champions/Ashe.h"
#include "Spells/Champions/AurelionSol.h"
#include "Spells/Champions/Azir.h"
#include "Spells/Champions/Bard.h"
#include "Spells/Champions/BelVeth.h"
#include "Spells/Champions/Blitzcrank.h"
#include "Spells/Champions/Brand.h"
#include "Spells/Champions/Braum.h"
#include "Spells/Champions/Caitlyn.h"
#include "Spells/Champions/Camille.h"
#include "Spells/Champions/Cassiopeia.h"
#include "Spells/Champions/ChoGath.h"
#include "Spells/Champions/Corki.h"
#include "Spells/Champions/Darius.h"
#include "Spells/Champions/Diana.h"
#include "Spells/Champions/Draven.h"
#include "Spells/Champions/DrMundo.h"
#include "Spells/Champions/Ekko.h"
#include "Spells/Champions/Elise.h"
#include "Spells/Champions/Evelynn.h"
#include "Spells/Champions/Ezreal.h"
#include "Spells/Champions/Fiddlesticks.h"
#include "Spells/Champions/Fiora.h"
#include "Spells/Champions/Fizz.h"
#include "Spells/Champions/Galio.h"
#include "Spells/Champions/Gangplank.h"
#include "Spells/Champions/Garen.h"
#include "Spells/Champions/Gnar.h"
#include "Spells/Champions/Gragas.h"
#include "Spells/Champions/Graves.h"
#include "Spells/Champions/Gwen.h"
#include "Spells/Champions/Hecarim.h"
#include "Spells/Champions/Heimerdinger.h"
#include "Spells/Champions/Illaoi.h"
#include "Spells/Champions/Irelia.h"
#include "Spells/Champions/Ivern.h"
#include "Spells/Champions/Janna.h"
#include "Spells/Champions/JarvanIV.h"
#include "Spells/Champions/Jax.h"
#include "Spells/Champions/Jayce.h"
#include "Spells/Champions/Jhin.h"
#include "Spells/Champions/Jinx.h"
#include "Spells/Champions/Kaisa.h"
#include "Spells/Champions/Kalista.h"
#include "Spells/Champions/Karma.h"
#include "Spells/Champions/Karthus.h"
#include "Spells/Champions/Kassadin.h"
#include "Spells/Champions/Katarina.h"
#include "Spells/Champions/Kayle.h"
#include "Spells/Champions/Kayn.h"
#include "Spells/Champions/Kennen.h"
#include "Spells/Champions/KhaZix.h"
#include "Spells/Champions/Kindred.h"
#include "Spells/Champions/Kled.h"
#include "Spells/Champions/KogMaw.h"
#include "Spells/Champions/KSante.h"
#include "Spells/Champions/Leblanc.h"
#include "Spells/Champions/LeeSin.h"
#include "Spells/Champions/Leona.h"
#include "Spells/Champions/Lillia.h"
#include "Spells/Champions/Lissandra.h"
#include "Spells/Champions/Lucian.h"
#include "Spells/Champions/Lulu.h"
#include "Spells/Champions/Lux.h"
#include "Spells/Champions/Malphite.h"
#include "Spells/Champions/Malzahar.h"
#include "Spells/Champions/Maokai.h"
#include "Spells/Champions/MasterYi.h"
#include "Spells/Champions/Milio.h"
#include "Spells/Champions/MissFortune.h"
#include "Spells/Champions/Mordekaiser.h"
#include "Spells/Champions/Morgana.h"
#include "Spells/Champions/Nami.h"
#include "Spells/Champions/Nasus.h"
#include "Spells/Champions/Nautilus.h"
#include "Spells/Champions/Neeko.h"
#include "Spells/Champions/Nidalee.h"
#include "Spells/Champions/Nilah.h"
#include "Spells/Champions/Nocturne.h"
#include "Spells/Champions/Nunu.h"
#include "Spells/Champions/Olaf.h"
#include "Spells/Champions/Orianna.h"
#include "Spells/Champions/Ornn.h"
#include "Spells/Champions/Pantheon.h"
#include "Spells/Champions/Poppy.h"
#include "Spells/Champions/Pyke.h"
#include "Spells/Champions/Qiyana.h"
#include "Spells/Champions/Quinn.h"
#include "Spells/Champions/Rakan.h"
#include "Spells/Champions/Rammus.h"
#include "Spells/Champions/RekSai.h"
#include "Spells/Champions/Rell.h"
#include "Spells/Champions/RenataGlasc.h"
#include "Spells/Champions/Renekton.h"
#include "Spells/Champions/Rengar.h"
#include "Spells/Champions/Riven.h"
#include "Spells/Champions/Rumble.h"
#include "Spells/Champions/Ryze.h"
#include "Spells/Champions/Samira.h"
#include "Spells/Champions/Sejuani.h"
#include "Spells/Champions/Senna.h"
#include "Spells/Champions/Seraphine.h"
#include "Spells/Champions/Sett.h"
#include "Spells/Champions/Shaco.h"
#include "Spells/Champions/Shen.h"
#include "Spells/Champions/Shyvana.h"
#include "Spells/Champions/Singed.h"
#include "Spells/Champions/Sion.h"
#include "Spells/Champions/Sivir.h"
#include "Spells/Champions/Skarner.h"
#include "Spells/Champions/Sona.h"
#include "Spells/Champions/Soraka.h"
#include "Spells/Champions/Sylas.h"
#include "Spells/Champions/TahmKench.h"
#include "Spells/Champions/Taliyah.h"
#include "Spells/Champions/Talon.h"
#include "Spells/Champions/Teemo.h"
#include "Spells/Champions/Thresh.h"
#include "Spells/Champions/Tristana.h"
#include "Spells/Champions/Trundle.h"
#include "Spells/Champions/Tryndamere.h"
#include "Spells/Champions/TwistedFate.h"
#include "Spells/Champions/Twitch.h"
#include "Spells/Champions/Udyr.h"
#include "Spells/Champions/Urgot.h"
#include "Spells/Champions/Varus.h"
#include "Spells/Champions/Vayne.h"
#include "Spells/Champions/Veigar.h"
#include "Spells/Champions/VelKoz.h"
#include "Spells/Champions/Vex.h"
#include "Spells/Champions/Vi.h"
#include "Spells/Champions/Viego.h"
#include "Spells/Champions/Viktor.h"
#include "Spells/Champions/Vladimir.h"
#include "Spells/Champions/Volibear.h"
#include "Spells/Champions/Warwick.h"
#include "Spells/Champions/Wukong.h"
#include "Spells/Champions/Xayah.h"
#include "Spells/Champions/Xerath.h"
#include "Spells/Champions/XinZhao.h"
#include "Spells/Champions/Yasuo.h"
#include "Spells/Champions/Yone.h"
#include "Spells/Champions/Yorick.h"
#include "Spells/Champions/Yuumi.h"
#include "Spells/Champions/Zac.h"
#include "Spells/Champions/Zed.h"
#include "Spells/Champions/Zeri.h"
#include "Spells/Champions/Ziggs.h"
#include "Spells/Champions/Zilean.h"
#include "Spells/Champions/Zoe.h"
#include "Spells/Champions/Zyra.h"

void DamageLib::initialize()
{
	dmg_lib->set_callbacks(
		&get_spell_damage,
		&calculate_damage,
		&get_auto_attack_damage
	);

	item_database->add(ItemId::Blade_of_the_Ruined_King, new Botrk());
	item_database->add(ItemId::Ceaseless_Hunger, new CeaselessHunger());
	item_database->add(ItemId::Dead_Mans_Plate, new DeadMansPlate());
	item_database->add(ItemId::Deicide, new Deicide());
	item_database->add(ItemId::Divine_Sunderer, new DivineSunderer());
	item_database->add(ItemId::Dorans_Ring, new DoransRing());
	item_database->add(ItemId::Dorans_Shield, new DoransShield());
	item_database->add(ItemId::Draktharrs_Shadowcarver, new DrakhtarrsShadowcarver());
	item_database->add(ItemId::Dreamshatter, new DreamShatter());
	item_database->add(ItemId::Duskblade_of_Draktharr, new DuskbladeOfDraktharr());
	item_database->add(ItemId::Essence_Reaver, new EssenceReaver());
	item_database->add(ItemId::Eternal_Winter, new EternalWinter());
	item_database->add(ItemId::Everfrost, new Everfrost());
	item_database->add(ItemId::Frozen_Fist, new FrozenFist());
	item_database->add(ItemId::Galeforce, new Galeforce());
	item_database->add(ItemId::Goredrinker, new Goredrinker());
	item_database->add(ItemId::Guinsoos_Rageblade, new GuinsooRageblade());
	item_database->add(ItemId::Hextech_Rocketbelt, new HextechRocketbelt());
	item_database->add(ItemId::Iceborn_Gauntlet, new IcebornGauntlet());
	item_database->add(ItemId::Infinity_Force, new InfinityForce());
	item_database->add(ItemId::Ironspike_Whip, new IronspikeWhip());
	item_database->add(ItemId::Kircheis_Shard, new KircheisShard());
	item_database->add(ItemId::Kraken_Slayer, new KrakenSlayer());
	item_database->add(ItemId::Lich_Bane, new LichBane());
	item_database->add(ItemId::Muramana, new Muramana());
	item_database->add(ItemId::Nashors_Tooth, new NashorsTooth());
	item_database->add(ItemId::Noonquiver, new Noonquiver());
	item_database->add(ItemId::Prowlers_Claw, new ProwlersClaw());
	item_database->add(ItemId::Rageknife, new Rageknife());
	item_database->add(ItemId::Rapid_Firecannon, new RapidFirecannon());
	item_database->add(ItemId::Recurve_Bow, new RecurveBow());
	item_database->add(ItemId::Runaans_Hurricane, new RunaanHurricane());
	item_database->add(ItemId::Seething_Sorrow, new SeethingSorrow());
	item_database->add(ItemId::Sheen, new Sheen());
	item_database->add(ItemId::Statikk_Shiv, new StatikkShiv());
	item_database->add(ItemId::Stormrazor, new Stormrazor());
	item_database->add(ItemId::Stridebreaker, new StrideBreaker());
	item_database->add(ItemId::Tear_of_the_Goddess, new TearOfTheGoddess());
	item_database->add(ItemId::Titanic_Hydra, new TitanicHydra());
	item_database->add(ItemId::Trinity_Force, new TrinityForce());
	item_database->add(ItemId::Typhoon, new Typhoon());
	item_database->add(ItemId::Upgraded_Aeropack, new UpgradedAeropack());
	item_database->add(ItemId::Wits_End, new WitsEnd());

	for (const auto& hero : entities->get_heroes())
	{
		switch (hero->get_character_hash())
		{
			case CharacterHash::Aatrox: {
				hero_database->add(CharacterHash::Aatrox, new Aatrox(hero));
				passive_database->add(CharacterHash::Aatrox, new AatroxPassive());
			}
			case CharacterHash::Ahri: {
				hero_database->add(CharacterHash::Ahri, new Ahri(hero));
			}
			case CharacterHash::Akali: {
				hero_database->add(CharacterHash::Akali, new Akali(hero));
				passive_database->add(CharacterHash::Akali, new AkaliPassive());
			}
			case CharacterHash::Akshan: {
				hero_database->add(CharacterHash::Akshan, new Akshan(hero));
				passive_database->add(CharacterHash::Akshan, new AkshanPassive());
			}
			case CharacterHash::Alistar: {
				hero_database->add(CharacterHash::Alistar, new Alistar(hero));
				passive_database->add(CharacterHash::Alistar, new AlistarPassive());
			}
			case CharacterHash::Amumu: {
				hero_database->add(CharacterHash::Amumu, new Amumu(hero));
			}
			case CharacterHash::Anivia: {
				hero_database->add(CharacterHash::Anivia, new Anivia(hero));
			}
			case CharacterHash::Annie: {
				hero_database->add(CharacterHash::Annie, new Annie(hero));
			}
			case CharacterHash::Aphelios: {
				hero_database->add(CharacterHash::Aphelios, new Aphelios(hero));
				passive_database->add(CharacterHash::Aphelios, new ApheliosPassive());
			}
			case CharacterHash::Ashe: {
				hero_database->add(CharacterHash::Ashe, new Ashe(hero));
				passive_database->add(CharacterHash::Ashe, new AshePassive());
			}
			case CharacterHash::AurelionSol: {
				hero_database->add(CharacterHash::AurelionSol, new AurelionSol(hero));
			}
			case CharacterHash::Azir: {
				hero_database->add(CharacterHash::Azir, new Azir(hero));
			}
			case CharacterHash::Bard: {
				hero_database->add(CharacterHash::Bard, new Bard(hero));
				passive_database->add(CharacterHash::Bard, new BardPassive());
			}
			case CharacterHash::Belveth: {
				hero_database->add(CharacterHash::Belveth, new BelVeth(hero));
				passive_database->add(CharacterHash::Belveth, new BelvethPassive());
			}
			case CharacterHash::Blitzcrank: {
				hero_database->add(CharacterHash::Blitzcrank, new Blitzcrank(hero));
				passive_database->add(CharacterHash::Blitzcrank, new BlitzcrankPassive());
			}
			case CharacterHash::Brand: {
				hero_database->add(CharacterHash::Brand, new Brand(hero));
			}
			case CharacterHash::Braum: {
				hero_database->add(CharacterHash::Braum, new Braum(hero));
				passive_database->add(CharacterHash::Braum, new BraumPassive());
				passive_database->add(CharacterHash::Unknown, new BraumMarkPassive());
			}
			case CharacterHash::Caitlyn: {
				hero_database->add(CharacterHash::Caitlyn, new Caitlyn(hero));
				passive_database->add(CharacterHash::Caitlyn, new CaitlynPassive());
			}
			case CharacterHash::Camille: {
				hero_database->add(CharacterHash::Camille, new Camille(hero));
				passive_database->add(CharacterHash::Camille, new CamillePassive());
			}
			case CharacterHash::Cassiopeia: {
				hero_database->add(CharacterHash::Cassiopeia, new Cassiopeia(hero));
			}
			case CharacterHash::Chogath: {
				hero_database->add(CharacterHash::Chogath, new ChoGath(hero));
				passive_database->add(CharacterHash::Chogath, new ChogathPassive());
			}
			case CharacterHash::Corki: {
				hero_database->add(CharacterHash::Corki, new Corki(hero));
				passive_database->add(CharacterHash::Corki, new CorkiPassive());
			}
			case CharacterHash::Darius: {
				hero_database->add(CharacterHash::Darius, new Darius(hero));
				passive_database->add(CharacterHash::Darius, new DariusPassive());
			}
			case CharacterHash::Diana: {
				hero_database->add(CharacterHash::Diana, new Diana(hero));
				passive_database->add(CharacterHash::Diana, new DianaPassive());
			}
			case CharacterHash::Draven: {
				hero_database->add(CharacterHash::Draven, new Draven(hero));
				passive_database->add(CharacterHash::Draven, new DravenPassive());
			}
			case CharacterHash::DrMundo: {
				hero_database->add(CharacterHash::DrMundo, new DrMundo(hero));
				passive_database->add(CharacterHash::DrMundo, new DrMundoPassive());
			}
			case CharacterHash::Ekko: {
				hero_database->add(CharacterHash::Ekko, new Ekko(hero));
				passive_database->add(CharacterHash::Ekko, new EkkoPassive());
			}
			case CharacterHash::Elise: {
				hero_database->add(CharacterHash::Elise, new Elise(hero));
				passive_database->add(CharacterHash::Elise, new ElisePassive());
			}
			case CharacterHash::Evelynn: {
				hero_database->add(CharacterHash::Evelynn, new Evelynn(hero));
			}
			case CharacterHash::Ezreal: {
				hero_database->add(CharacterHash::Ezreal, new Ezreal(hero));
				passive_database->add(CharacterHash::Ezreal, new EzrealPassive());
			}
			case CharacterHash::Fiddlesticks: {
				hero_database->add(CharacterHash::Fiddlesticks, new Fiddlesticks(hero));
			}
			case CharacterHash::Fiora: {
				hero_database->add(CharacterHash::Fiora, new Fiora(hero));
				passive_database->add(CharacterHash::Fiora, new FioraPassive());
			}
			case CharacterHash::Fizz: {
				hero_database->add(CharacterHash::Fizz, new Fizz(hero));
				passive_database->add(CharacterHash::Fizz, new FizzPassive());
			}
			case CharacterHash::Galio: {
				hero_database->add(CharacterHash::Galio, new Galio(hero));
				passive_database->add(CharacterHash::Galio, new GalioPassive());
			}
			case CharacterHash::Gangplank: {
				hero_database->add(CharacterHash::Gangplank, new Gangplank(hero));
				passive_database->add(CharacterHash::Gangplank, new GangplankPassive());
			}
			case CharacterHash::Garen: {
				hero_database->add(CharacterHash::Garen, new Garen(hero));
				passive_database->add(CharacterHash::Garen, new GarenPassive());
			}
			case CharacterHash::Gnar: {
				hero_database->add(CharacterHash::Gnar, new Gnar(hero));
				passive_database->add(CharacterHash::Gnar, new GnarPassive());
			}
			case CharacterHash::Gragas: {
				hero_database->add(CharacterHash::Gragas, new Gragas(hero));
				passive_database->add(CharacterHash::Gragas, new GragasPassive());
			}
			case CharacterHash::Graves: {
				hero_database->add(CharacterHash::Graves, new Graves(hero));
			}
			case CharacterHash::Gwen: {
				hero_database->add(CharacterHash::Gwen, new Gwen(hero));
				passive_database->add(CharacterHash::Gwen, new GwenPassive());
			}
			case CharacterHash::Hecarim: {
				hero_database->add(CharacterHash::Hecarim, new Hecarim(hero));
				passive_database->add(CharacterHash::Hecarim, new HecarimPassive());
			}
			case CharacterHash::Heimerdinger: {
				hero_database->add(CharacterHash::Heimerdinger, new Heimerdinger(hero));
			}
			case CharacterHash::Illaoi: {
				hero_database->add(CharacterHash::Illaoi, new Illaoi(hero));
				passive_database->add(CharacterHash::Illaoi, new IllaoiPassive());
			}
			case CharacterHash::Irelia: {
				hero_database->add(CharacterHash::Irelia, new Irelia(hero));
				passive_database->add(CharacterHash::Irelia, new IreliaPassive());
			}
			case CharacterHash::Ivern: {
				hero_database->add(CharacterHash::Ivern, new Ivern(hero));
				passive_database->add(CharacterHash::Ivern, new IvernPassive());
			}
			case CharacterHash::Janna: {
				hero_database->add(CharacterHash::Janna, new Janna(hero));
			}
			case CharacterHash::JarvanIV: {
				hero_database->add(CharacterHash::JarvanIV, new JarvanIV(hero));
				passive_database->add(CharacterHash::JarvanIV, new JarvanPassive());
			}
			case CharacterHash::Jax: {
				hero_database->add(CharacterHash::Jax, new Jax(hero));
				passive_database->add(CharacterHash::Jax, new JaxPassive());
			}
			case CharacterHash::Jayce: {
				hero_database->add(CharacterHash::Jayce, new Jayce(hero));
				passive_database->add(CharacterHash::Jayce, new JaycePassive());
			}
			case CharacterHash::Jhin: {
				hero_database->add(CharacterHash::Jhin, new Jhin(hero));
				passive_database->add(CharacterHash::Jhin, new JhinPassive());
			}
			case CharacterHash::Jinx: {
				hero_database->add(CharacterHash::Jinx, new Jinx(hero));
				passive_database->add(CharacterHash::Jinx, new JinxPassive());
			}
			case CharacterHash::Kaisa: {
				hero_database->add(CharacterHash::Kaisa, new Kaisa(hero));
				passive_database->add(CharacterHash::Kaisa, new KaisaPassive());
			}
			case CharacterHash::Kalista: {
				hero_database->add(CharacterHash::Kalista, new Kalista(hero));
				passive_database->add(CharacterHash::Kalista, new KalistaPassive());
				passive_database->add(CharacterHash::Unknown, new KalistaMarkPassive());
			}
			case CharacterHash::Karma: {
				hero_database->add(CharacterHash::Karma, new Karma(hero));
			}
			case CharacterHash::Karthus: {
				hero_database->add(CharacterHash::Karthus, new Karthus(hero));
			}
			case CharacterHash::Kassadin: {
				hero_database->add(CharacterHash::Kassadin, new Kassadin(hero));
				passive_database->add(CharacterHash::Kassadin, new KassadinPassive());
			}
			case CharacterHash::Katarina: {
				hero_database->add(CharacterHash::Katarina, new Katarina(hero));
			}
			case CharacterHash::Kayle: {
				hero_database->add(CharacterHash::Kayle, new Kayle(hero));
				passive_database->add(CharacterHash::Kayle, new KaylePassive());
			}
			case CharacterHash::Kayn: {
				hero_database->add(CharacterHash::Kayn, new Kayn(hero));
			}
			case CharacterHash::Kennen: {
				hero_database->add(CharacterHash::Kennen, new Kennen(hero));
				passive_database->add(CharacterHash::Kennen, new KennenPassive());
			}
			case CharacterHash::Khazix: {
				hero_database->add(CharacterHash::Khazix, new KhaZix(hero));
				passive_database->add(CharacterHash::Khazix, new KhazixPassive());
			}
			case CharacterHash::Kindred: {
				hero_database->add(CharacterHash::Kindred, new Kindred(hero));
			}
			case CharacterHash::Kled: {
				hero_database->add(CharacterHash::Kled, new Kled(hero));
				passive_database->add(CharacterHash::Kled, new KledPassive());
			}
			case CharacterHash::KogMaw: {
				hero_database->add(CharacterHash::KogMaw, new KogMaw(hero));
				passive_database->add(CharacterHash::KogMaw, new KogmawPassive());
			}
			case CharacterHash::KSante: {
				hero_database->add(CharacterHash::KSante, new KSante(hero));
			}
			case CharacterHash::Leblanc: {
				hero_database->add(CharacterHash::Leblanc, new Leblanc(hero));
			}
			case CharacterHash::LeeSin: {
				hero_database->add(CharacterHash::LeeSin, new LeeSin(hero));
			}
			case CharacterHash::Leona: {
				hero_database->add(CharacterHash::Leona, new Leona(hero));
				passive_database->add(CharacterHash::Leona, new LeonaPassive());
			}
			case CharacterHash::Lillia: {
				hero_database->add(CharacterHash::Lillia, new Lillia(hero));
			}
			case CharacterHash::Lissandra: {
				hero_database->add(CharacterHash::Lissandra, new Lissandra(hero));
			}
			case CharacterHash::Lucian: {
				hero_database->add(CharacterHash::Lucian, new Lucian(hero));
				passive_database->add(CharacterHash::Lucian, new LucianPassive());
			}
			case CharacterHash::Lulu: {
				hero_database->add(CharacterHash::Lulu, new Lulu(hero));
			}
			case CharacterHash::Lux: {
				hero_database->add(CharacterHash::Lux, new Lux(hero));
				passive_database->add(CharacterHash::Lux, new LuxPassive());
			}
			case CharacterHash::Malphite: {
				hero_database->add(CharacterHash::Malphite, new Malphite(hero));
				passive_database->add(CharacterHash::Malphite, new MalphitePassive());
			}
			case CharacterHash::Malzahar: {
				hero_database->add(CharacterHash::Malzahar, new Malzahar(hero));
			}
			case CharacterHash::Maokai: {
				hero_database->add(CharacterHash::Maokai, new Maokai(hero));
			}
			case CharacterHash::MasterYi: {
				hero_database->add(CharacterHash::MasterYi, new MasterYi(hero));
				passive_database->add(CharacterHash::MasterYi, new MasterYiPassive());
			}
			case CharacterHash::Milio: {
				hero_database->add(CharacterHash::Milio, new Milio(hero));
			}
			case CharacterHash::MissFortune: {
				hero_database->add(CharacterHash::MissFortune, new MissFortune(hero));
				passive_database->add(CharacterHash::MissFortune, new MissFortunePassive());
			}
			case CharacterHash::MonkeyKing: {
				hero_database->add(CharacterHash::MonkeyKing, new Wukong(hero));
				passive_database->add(CharacterHash::MonkeyKing, new MonkeyKingPassive());
			}
			case CharacterHash::Mordekaiser: {
				hero_database->add(CharacterHash::Mordekaiser, new Mordekaiser(hero));
			}
			case CharacterHash::Morgana: {
				hero_database->add(CharacterHash::Morgana, new Morgana(hero));
			}
			case CharacterHash::Nami: {
				hero_database->add(CharacterHash::Nami, new Nami(hero));
				passive_database->add(CharacterHash::Unknown, new NamiMarkPassive());
			}
			case CharacterHash::Nasus: {
				hero_database->add(CharacterHash::Nasus, new Nasus(hero));
				passive_database->add(CharacterHash::Nasus, new NasusPassive());
			}
			case CharacterHash::Nautilus: {
				hero_database->add(CharacterHash::Nautilus, new Nautilus(hero));
				passive_database->add(CharacterHash::Nautilus, new NautilusPassive());
			}
			case CharacterHash::Neeko: {
				hero_database->add(CharacterHash::Neeko, new Neeko(hero));
				passive_database->add(CharacterHash::Neeko, new NeekoPassive());
			}
			case CharacterHash::Nidalee: {
				hero_database->add(CharacterHash::Nidalee, new Nidalee(hero));
				passive_database->add(CharacterHash::Nidalee, new NidaleePassive());
			}
			case CharacterHash::Nilah: {
				hero_database->add(CharacterHash::Nilah, new Nilah(hero));
			}
			case CharacterHash::Nocturne: {
				hero_database->add(CharacterHash::Nocturne, new Nocturne(hero));
				passive_database->add(CharacterHash::Nocturne, new NocturnePassive());
			}
			case CharacterHash::Nunu: {
				hero_database->add(CharacterHash::Nunu, new Nunu(hero));
			}
			case CharacterHash::Olaf: {
				hero_database->add(CharacterHash::Olaf, new Olaf(hero));
			}
			case CharacterHash::Orianna: {
				hero_database->add(CharacterHash::Orianna, new Orianna(hero));
				passive_database->add(CharacterHash::Orianna, new OriannaPassive());
			}
			case CharacterHash::Ornn: {
				hero_database->add(CharacterHash::Ornn, new Ornn(hero));
				passive_database->add(CharacterHash::Ornn, new OrnnPassive());
			}
			case CharacterHash::Pantheon: {
				hero_database->add(CharacterHash::Pantheon, new Pantheon(hero));
			}
			case CharacterHash::Poppy: {
				hero_database->add(CharacterHash::Poppy, new Poppy(hero));
				passive_database->add(CharacterHash::Poppy, new PoppyPassive());
			}
			case CharacterHash::Pyke: {
				hero_database->add(CharacterHash::Pyke, new Pyke(hero));
			}
			case CharacterHash::Qiyana: {
				hero_database->add(CharacterHash::Qiyana, new Qiyana(hero));
				passive_database->add(CharacterHash::Qiyana, new QiyanaPassive());
			}
			case CharacterHash::Quinn: {
				hero_database->add(CharacterHash::Quinn, new Quinn(hero));
				passive_database->add(CharacterHash::Quinn, new QuinnPassive());
			}
			case CharacterHash::Rakan: {
				hero_database->add(CharacterHash::Rakan, new Rakan(hero));
			}
			case CharacterHash::Rammus: {
				hero_database->add(CharacterHash::Rammus, new Rammus(hero));
				passive_database->add(CharacterHash::Rammus, new RammusPassive());
			}
			case CharacterHash::RekSai: {
				hero_database->add(CharacterHash::RekSai, new RekSai(hero));
				passive_database->add(CharacterHash::RekSai, new RekSaiPassive());
			}
			case CharacterHash::Rell: {
				hero_database->add(CharacterHash::Rell, new Rell(hero));
			}
			case CharacterHash::Renata: {
				hero_database->add(CharacterHash::Renata, new RenataGlasc(hero));
				passive_database->add(CharacterHash::Renata, new RenataPassive());
				passive_database->add(CharacterHash::Unknown, new RenataMarkPassive());
			}
			case CharacterHash::Renekton: {
				hero_database->add(CharacterHash::Renekton, new Renekton(hero));
				passive_database->add(CharacterHash::Renekton, new RenektonPassive());
			}
			case CharacterHash::Rengar: {
				hero_database->add(CharacterHash::Rengar, new Rengar(hero));
				passive_database->add(CharacterHash::Rengar, new RengarPassive());
			}
			case CharacterHash::Riven: {
				hero_database->add(CharacterHash::Riven, new Riven(hero));
				passive_database->add(CharacterHash::Riven, new RivenPassive());
			}
			case CharacterHash::Rumble: {
				hero_database->add(CharacterHash::Rumble, new Rumble(hero));
				passive_database->add(CharacterHash::Rumble, new RumblePassive());
			}
			case CharacterHash::Ryze: {
				hero_database->add(CharacterHash::Ryze, new Ryze(hero));
			}
			case CharacterHash::Samira: {
				hero_database->add(CharacterHash::Samira, new Samira(hero));
				passive_database->add(CharacterHash::Samira, new SamiraPassive());
			}
			case CharacterHash::Sejuani: {
				hero_database->add(CharacterHash::Sejuani, new Sejuani(hero));
				passive_database->add(CharacterHash::Sejuani, new SejuaniPassive());
			}
			case CharacterHash::Senna: {
				hero_database->add(CharacterHash::Senna, new Senna(hero));
			}
			case CharacterHash::Seraphine: {
				hero_database->add(CharacterHash::Seraphine, new Seraphine(hero));
			}
			case CharacterHash::Sett: {
				hero_database->add(CharacterHash::Sett, new Sett(hero));
				passive_database->add(CharacterHash::Sett, new SettPassive());
			}
			case CharacterHash::Shaco: {
				hero_database->add(CharacterHash::Shaco, new Shaco(hero));
				passive_database->add(CharacterHash::Shaco, new ShacoPassive());
			}
			case CharacterHash::Shen: {
				hero_database->add(CharacterHash::Shen, new Shen(hero));
				passive_database->add(CharacterHash::Shen, new ShenPassive());
			}
			case CharacterHash::Shyvana: {
				hero_database->add(CharacterHash::Shyvana, new Shyvana(hero));
				passive_database->add(CharacterHash::Shyvana, new ShyvanaPassive());
			}
			case CharacterHash::Singed: {
				hero_database->add(CharacterHash::Singed, new Singed(hero));
			}
			case CharacterHash::Sion: {
				hero_database->add(CharacterHash::Sion, new Sion(hero));
				passive_database->add(CharacterHash::Sion, new SionPassive());
			}
			case CharacterHash::Sivir: {
				hero_database->add(CharacterHash::Sivir, new Sivir(hero));
			}
			case CharacterHash::Skarner: {
				hero_database->add(CharacterHash::Skarner, new Skarner(hero));
				passive_database->add(CharacterHash::Skarner, new SkarnerPassve());
			}
			case CharacterHash::Sona: {
				hero_database->add(CharacterHash::Sona, new Sona(hero));
				passive_database->add(CharacterHash::Sona, new SonaPassive());
				passive_database->add(CharacterHash::Unknown, new SonaMarkPassive());
			}
			case CharacterHash::Soraka: {
				hero_database->add(CharacterHash::Soraka, new Soraka(hero));
			}
			case CharacterHash::Sylas: {
				hero_database->add(CharacterHash::Sylas, new Sylas(hero));
				passive_database->add(CharacterHash::Sylas, new SylasPassive());
		    }
			case CharacterHash::TahmKench: {
				hero_database->add(CharacterHash::TahmKench, new TahmKench(hero));
				passive_database->add(CharacterHash::TahmKench, new TahmKenchPassive());
			}
			case CharacterHash::Taliyah: {
				hero_database->add(CharacterHash::Taliyah, new Taliyah(hero));
			}
			case CharacterHash::Talon: {
				hero_database->add(CharacterHash::Talon, new Talon(hero));
				passive_database->add(CharacterHash::Talon, new TalonPassive());
			}
			case CharacterHash::Teemo: {
				hero_database->add(CharacterHash::Teemo, new Teemo(hero));
				passive_database->add(CharacterHash::Teemo, new TeemoPassive());
			}
			case CharacterHash::Thresh: {
				hero_database->add(CharacterHash::Thresh, new Thresh(hero));
				passive_database->add(CharacterHash::Thresh, new ThreshPassive());
			}
			case CharacterHash::Tristana: {
				hero_database->add(CharacterHash::Tristana, new Tristana(hero));
			}
			case CharacterHash::Trundle: {
				hero_database->add(CharacterHash::Trundle, new Trundle(hero));
				passive_database->add(CharacterHash::Trundle, new TrundlePassive());
			}
			case CharacterHash::Tryndamere: {
				hero_database->add(CharacterHash::Tryndamere, new Tryndamere(hero));
			}
			case CharacterHash::TwistedFate: {
				hero_database->add(CharacterHash::TwistedFate, new TwistedFate(hero));
				passive_database->add(CharacterHash::TwistedFate, new TwistedFatePassive());
			}
			case CharacterHash::Twitch: {
				hero_database->add(CharacterHash::Twitch, new Twitch(hero));
			}
			case CharacterHash::Udyr: {
				hero_database->add(CharacterHash::Udyr, new Udyr(hero));
				passive_database->add(CharacterHash::Udyr, new UdyrPassive());
			}
			case CharacterHash::Urgot: {
				hero_database->add(CharacterHash::Urgot, new Urgot(hero));
				passive_database->add(CharacterHash::Urgot, new UrgotPassive());
			}
			case CharacterHash::Varus: {
				hero_database->add(CharacterHash::Varus, new Varus(hero));
				passive_database->add(CharacterHash::Varus, new VarusPassive());
			}
			case CharacterHash::Vayne: {
				hero_database->add(CharacterHash::Vayne, new Vayne(hero));
				passive_database->add(CharacterHash::Vayne, new VaynePassive());
			}
			case CharacterHash::Veigar: {
				hero_database->add(CharacterHash::Veigar, new Veigar(hero));
			}
			case CharacterHash::Velkoz: {
				hero_database->add(CharacterHash::Velkoz, new VelKoz(hero));
			}
			case CharacterHash::Vex: {
				hero_database->add(CharacterHash::Vex, new Vex(hero));
				passive_database->add(CharacterHash::Vex, new VexPassive());
			}
			case CharacterHash::Vi: {
				hero_database->add(CharacterHash::Vi, new Vi(hero));
				passive_database->add(CharacterHash::Vi, new ViPassive());
			}
			case CharacterHash::Viego: {
				hero_database->add(CharacterHash::Viego, new Viego(hero));
			}
			case CharacterHash::Viktor: {
				hero_database->add(CharacterHash::Viktor, new Viktor(hero));
			}
			case CharacterHash::Vladimir: {
				hero_database->add(CharacterHash::Vladimir, new Vladimir(hero));
			}
			case CharacterHash::Volibear: {
				hero_database->add(CharacterHash::Volibear, new Volibear(hero));
				passive_database->add(CharacterHash::Volibear, new VolibearPassive());
			}
			case CharacterHash::Warwick: {
				hero_database->add(CharacterHash::Warwick, new Warwick(hero));
				passive_database->add(CharacterHash::Warwick, new WarwickPassive());
			}
			case CharacterHash::Xayah: {
				hero_database->add(CharacterHash::Xayah, new Xayah(hero));
				passive_database->add(CharacterHash::Unknown, new XayahMarkPassive());
			}
			case CharacterHash::Xerath: {
				hero_database->add(CharacterHash::Xerath, new Xerath(hero));
			}
			case CharacterHash::XinZhao: {
				hero_database->add(CharacterHash::XinZhao, new XinZhao(hero));
				passive_database->add(CharacterHash::XinZhao, new XinZhaoPassive());
			}
			case CharacterHash::Yasuo: {
				hero_database->add(CharacterHash::Yasuo, new Yasuo(hero));
				passive_database->add(CharacterHash::Yasuo, new YasuoPassive());
			}
			case CharacterHash::Yone: {
				hero_database->add(CharacterHash::Yone, new Yone(hero));
			}
			case CharacterHash::Yorick: {
				hero_database->add(CharacterHash::Yorick, new Yorick(hero));
				passive_database->add(CharacterHash::Yorick, new YorickPassive());
			}
			case CharacterHash::Yuumi: {
				hero_database->add(CharacterHash::Yuumi, new Yuumi(hero));
			}
			case CharacterHash::Zac: {
				hero_database->add(CharacterHash::Zac, new Zac(hero));
			}
			case CharacterHash::Zed: {
				hero_database->add(CharacterHash::Zed, new Zed(hero));
			}
			case CharacterHash::Zeri: {
				hero_database->add(CharacterHash::Zeri, new Zeri(hero));
				passive_database->add(CharacterHash::Zeri, new ZeriPassive());
			}
			case CharacterHash::Ziggs: {
				hero_database->add(CharacterHash::Ziggs, new Ziggs(hero));
				passive_database->add(CharacterHash::Ziggs, new ZiggsPassive());
			}
			case CharacterHash::Zilean: {
				hero_database->add(CharacterHash::Zilean, new Zilean(hero));
			}
			case CharacterHash::Zoe: {
				hero_database->add(CharacterHash::Zoe, new Zoe(hero));
				passive_database->add(CharacterHash::Zoe, new ZoePassive());
			}
			case CharacterHash::Zyra: {
				hero_database->add(CharacterHash::Zyra, new Zyra(hero));
			}
			default:
				break;
		}

	}
}

void DamageLib::on_unload()
{
	item_database->clear();
	passive_database->clear();
	hero_database->clear();

	delete item_database;
	delete passive_database;
	delete hero_database;
}

std::list<CharacterHash> noCritFixChampions {
	CharacterHash::Ashe,
	CharacterHash::Corki,
	CharacterHash::Fiora,
	CharacterHash::Galio,
	CharacterHash::Graves,
	CharacterHash::Jayce,
	CharacterHash::Kayle,
	CharacterHash::Kled,
	CharacterHash::Pantheon,
	CharacterHash::Shaco,
	CharacterHash::Urgot,
	CharacterHash::Yasuo,
	CharacterHash::Zac,
	CharacterHash::Zeri
};

DamageOutput DamageLib::get_spell_damage(GameObject* source, GameObject* target, SlotId spell_slot, int stage, int stacks)
{
	if (!source || !target)
		return { };

	DamageChamp* damage_champ = hero_database->get(source);

	if (!damage_champ)
		return { };

	if (spell_slot > SlotId::R)
		return get_auto_attack_damage(source, target);

	SpellSlot* spell = source->get_spell(spell_slot);

	if (!spell)
		return { };

	const int spellLevel = spell->get_level();

	if (spellLevel == 0)
		return { };
	
	DamageOutput damage = damage_champ->get_damage(target, spell_slot, spellLevel, stage, stacks);
	const DamageSpell* damage_spell = damage_champ->get_spell(spell_slot);

	if (!damage_spell)
		return damage;

	if (damage_spell->has_on_hit)
	{
		for (const auto item : source->get_items())
		{
			const auto damage_item = item_database->get(item);
			if (!damage_item || !damage_item->is_active(source, target))
				continue;

			if (damage_item->damageType == DamageType::Magical)
				damage.magical += damage_spell->on_hit_ratio * (double)compute_damage(source, target, damage_item->damageType, damage_item->get_passive_damage(source, target, false));
			if (damage_item->damageType == DamageType::Physical)
				damage.physical += damage_spell->on_hit_ratio * (double)compute_damage(source, target, damage_item->damageType, damage_item->get_passive_damage(source, target, false));
		}
	}

	return damage;
}

double DamageLib::calculate_damage(GameObject* source, GameObject* target, DamageType damage_type, double base_damage)
{
	return compute_damage(source, target, damage_type, base_damage);
}

DamageOutput DamageLib::get_auto_attack_damage(GameObject* source, GameObject* target, bool include_passive, bool include_items)
{
	if (!source || !target)
		return { };

	if (!target->is_turret() && !target->is_minion() && !target->is_hero())
		return { };

	if (!source->is_turret() && !source->is_minion() && !source->is_hero())
		return { };

	if (source->is_turret() && target->is_minion())
	{
		if (target->is_melee() && !target->is_super_minion())
			return { 0.0, .45 * target->get_max_health(), 0.0 };
		if (target->is_ranged() && !target->is_super_minion())
			return { 0.0, .70 * target->get_max_health(), 0.0 };

		if (target->is_siege_minion())
		{
			switch (source->get_turret_type())
			{
			case TurretType::TierOne:
				return { 0.0, .14 * target->get_max_health(), 0.0 };
			case TurretType::TierTwo:
				return { 0.0, .11 * target->get_max_health(), 0.0 };
			case TurretType::TierThree:
			case TurretType::TierFour:
				return { 0.0, .08 * target->get_max_health(), 0.0 };
			default:
				return { };
			}
		}

		if (target->is_super_minion())
			return { 0.0, .05 * target->get_max_health(), 0.0 };
	}

	DamageOutput attackDamage = compute_physical_damage(source, target, source->get_total_ad());

	if (source->is_minion() && target->is_minion())
		return attackDamage;

	double multiplier = 1.0;

	if (include_passive)
	{
		if (target->is_minion() && target->is_enemy() && !target->is_neutral() && (source->has_buff(0x2ed1e7bb) || source->has_buff(0x858276d5) || source->has_buff(0x68a5c35f)) && source->count_allies_in_range(1100) > 0 && target->get_health_percent() < (source->is_melee() ? 50.0 : 30.0))
		{
			return { 9999999, 9999999, 9999999 };
		}

		const auto passiveDamage = passive_database->get(source);

		if (passiveDamage && passiveDamage->is_active(source, target) && passiveDamage->overwrite_attack_damage(source))
		{
			const auto damageOutput = passiveDamage->get_damage(source, target);
			const DamageType damageType = damageOutput.get_damage_type();
			attackDamage = compute_damage(source, target, damageType, damageType == DamageType::Magical ? damageOutput.magical : damageOutput.physical);
			attackDamage.raw += damageOutput.raw;
		}

		const bool flag = abs(source->get_crit() - 1.f) < 1.4012984643248171E-45;
		const auto charHash = source->get_character_hash();

		if (flag 
			&& (
				(charHash == CharacterHash::Fiora && !source->has_buff(0x6cf0cfb3) && !source->has_buff(0x0016a813))
			|| (charHash == CharacterHash::Galio && !source->has_buff(0x9c13438d))
			|| (charHash == CharacterHash::Jayce && !source->has_buff(0x0e95d0e7))
			|| (charHash == CharacterHash::Kayle && !source->has_buff(0x6280f79a))
				))
		{
			attackDamage.physical += source->get_total_ad() * ((double)get_crit_mulitplier(source) - 1.0);
		}

		if (charHash == CharacterHash::Jhin && (flag || source->has_buff(0xac3fa0c8)))
			attackDamage.physical *= 0.86 * (double)get_crit_mulitplier(source);

		if (std::find(noCritFixChampions.begin(), noCritFixChampions.end(), charHash) == noCritFixChampions.end() && flag)
			attackDamage.physical *= (double)get_crit_mulitplier(source);

		for (const auto& passive : passive_database->get_common_passives())
		{
			if (!passive || !passive->is_active(source, target) || passive->overwrite_attack_damage(source))
				continue;

			const auto damageOutput = passive->get_damage(source, target);
			const auto damageType = damageOutput.get_damage_type();
			attackDamage += compute_damage(source, target, damageType, damageType == DamageType::Magical ? damageOutput.magical : damageOutput.physical);
			attackDamage.raw += damageOutput.raw;
		}

		if (target->get_character_hash() == CharacterHash::Fizz)
		{
			float val1 = (float)(4.0 + 0.0099999997764825821 * (double) target->get_ap());
			attackDamage.physical -= std::min((double)val1, attackDamage.physical * 0.5);
		}

		if (target->get_item(ItemId::Wardens_Mail) || target->get_item(ItemId::Frozen_Heart) || target->get_item(ItemId::Randuins_Omen))
			multiplier *= 1.0 - std::min(20.0, 0.004999999888241291 * (double) target->get_max_health()) / 100.0;
	}

	if (include_items)
	{
		for (const auto item : source->get_items())
		{
			const auto damage_item = item_database->get(item);
			if (!damage_item || !damage_item->is_active(source, target))
				continue;

			attackDamage += compute_damage(source, target, source->get_character_hash() == CharacterHash::Zeri ? DamageType::Magical : damage_item->damageType, damage_item->get_passive_damage(source, target, true));
		}
	}

	attackDamage.physical = std::max(floor(attackDamage.physical * multiplier), 0.0);

	if (source->has_item(ItemId::The_Collector) && target->get_max_health() / (target->get_health() - (double)attackDamage) < .05)
		return { 0.0, 0.0, 999999 };

	return attackDamage;
}

DamageOutput DamageLib::compute_damage(GameObject* source, GameObject* target, DamageType damage_type, double amount)
{
	if (!source || !target)
		return { };

	switch (damage_type)
	{
	case DamageType::Physical:
		return compute_physical_damage(source, target, amount);
	case DamageType::Magical:
		return compute_magical_damage(source, target, amount);
	default:
		return { 0, 0, amount };
	}
}

DamageOutput DamageLib::compute_physical_damage(GameObject* source, GameObject* target, double amount)
{
	if (!source || !target || amount <= 0.f)
		return { };

	if (target->get_armor() <= 1.f)
		return { 0.0, amount, 0.0 };

	float flatArmorPen = source->get_lethality() * (.6f + .4f * source->get_level() / 18.f);
	float multiArmorPen = source->get_armor_pen_multiplier();
	float targetBonusArmor = target->get_bonus_armor();
	float targetBaseArmor = target->get_armor() - targetBonusArmor;

	if (source->is_minion() || source->is_turret())
		multiArmorPen = 1.f;

	targetBonusArmor -= targetBonusArmor * (1 - multiArmorPen);
	float targetArmor = (targetBaseArmor + targetBonusArmor) - flatArmorPen;

	float damageMultiplier;

	if (targetArmor >= 0.f)
		damageMultiplier = 100 / (100 + targetArmor);
	else
		damageMultiplier = 2 - (100 / (100 - targetArmor));

	return { 0.0, std::max(amount *= damageMultiplier, 0.0), 0.0 };
}

DamageOutput DamageLib::compute_magical_damage(GameObject* source, GameObject* target, double amount)
{
	if (!source || !target || amount <= 0.0)
		return { };

	if (target->get_spell_block() <= 1.f)
		return { amount, 0.0, 0.0 };

	float flatMagicPen = source->get_magic_pen_flat();
	float multiMagicPen = source->get_magic_pen_multiplier();
	float targetMagicRes = target->get_spell_block();

	targetMagicRes -= targetMagicRes * (1 - multiMagicPen);

	if (targetMagicRes >= 0.f)
		targetMagicRes -= flatMagicPen;

	float damageMultiplier;

	if (targetMagicRes >= 0.f)
		damageMultiplier = 100 / (100 + targetMagicRes);
	else
		damageMultiplier = 2 - (100 / (100 - targetMagicRes));

	DamageOutput ret;

	ret.magical = std::max(amount *= damageMultiplier, 0.0);

	// cursedtouch
	if (target->has_buff(0x8c10c58a))
		ret.raw = ret.magical * .01;

	return ret;
}

float DamageLib::get_crit_mulitplier(GameObject* source)
{
	if (!source)
		return 0.f;

	float num = 1.f;

	if (source->get_item(ItemId::Rageknife) || source->get_item(ItemId::Guinsoos_Rageblade) || source->get_item(ItemId::Seething_Sorrow))
		num = 0.f;
	if (source->get_item(ItemId::Infinity_Edge) || source->get_item(ItemId::Edge_of_Finality))
		num = .35f;

	return (double) (source->get_crit() - 1.f) >= 1.4012984643248171E-45 ? 1.f : 1.f + num;
}