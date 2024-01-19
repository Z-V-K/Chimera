#include "EvadeDB.h"

#include "Champions/Aatrox.h"
#include "Champions/Ahri.h"
#include "Champions/Akali.h"
#include "Champions/Akshan.h"
#include "Champions/Alistar.h"
#include "Champions/Amumu.h"
#include "Champions/Anivia.h"
#include "Champions/Annie.h"
#include "Champions/Aphelios.h"
#include "Champions/Ashe.h"
#include "Champions/AurelionSol.h"
#include "Champions/Azir.h"
#include "Champions/Belveth.h"
#include "Champions/Blitzcrank.h"
#include "Champions/Bard.h"
#include "Champions/Brand.h"
#include "Champions/Braum.h"
#include "Champions/Caitlyn.h"
#include "Champions/Camille.h"
#include "Champions/Cassiopeia.h"
#include "Champions/ChoGath.h"
#include "Champions/Corki.h"
#include "Champions/Darius.h"
#include "Champions/Diana.h"
#include "Champions/Draven.h"
#include "Champions/DrMundo.h"
#include "Champions/Ekko.h"
#include "Champions/Elise.h"
#include "Champions/Evelynn.h"
#include "Champions/Ezreal.h"
#include "Champions/Fiddlesticks.h"
#include "Champions/Fiora.h"
#include "Champions/Fizz.h"
#include "Champions/Galio.h"
#include "Champions/Gangplank.h"
#include "Champions/Gnar.h"
#include "Champions/Graves.h"
#include "Champions/Gwen.h"
#include "Champions/Hecarim.h"
#include "Champions/Heimerdinger.h"
#include "Champions/Poppy.h"
#include "Champions/Veigar.h"
#include "Champions/Illaoi.h"
#include "Champions/Irelia.h"
#include "Champions/Ivern.h"
#include "Champions/Janna.h"
#include "Champions/Jarvan.h"
#include "Champions/Jayce.h"
#include "Champions/Jhin.h"
#include "Champions/Jinx.h"
#include "Champions/Kaisa.h"
#include "Champions/Kalista.h"
#include "Champions/Karma.h"
#include "Champions/Karthus.h"
#include "Champions/Kassadin.h"
#include "Champions/Katarina.h"
#include "Champions/Kayle.h"
#include "Champions/Kayn.h"
#include "Champions/Kennen.h"
#include "Champions/Khazix.h"
#include "Champions/Kled.h"
#include "Champions/KogMaw.h"
#include "Champions/LeBlanc.h"
#include "Champions/LeeSin.h"
#include "Champions/Leona.h"
#include "Champions/Lillia.h"
#include "Champions/Lissandra.h"
#include "Champions/Lucian.h"
#include "Champions/Lulu.h"
#include "Champions/Lux.h"
#include "Champions/Malphite.h"
#include "Champions/Malzahar.h"
#include "Champions/Maokai.h"
#include "Champions/Mordekaiser.h"
#include "Champions/Morgana.h"
#include "Champions/Nami.h"
#include "Champions/Nautilus.h"
#include "Champions/Neeko.h"
#include "Champions/Nidalee.h"
#include "Champions/Nilah.h"
#include "Champions/Nocturne.h"
#include "Champions/Olaf.h"
#include "Champions/Orianna.h"
#include "Champions/Ornn.h"
#include "Champions/Pantheon.h"
#include "Champions/Pyke.h"
#include "Champions/Qiyana.h"
#include "Champions/Quinn.h"
#include "Champions/Rakan.h"
#include "Champions/Rammus.h"
#include "Champions/RekSai.h"
#include "Champions/Rell.h"
#include "Champions/Renata.h"
#include "Champions/Renekton.h"
#include "Champions/Riven.h"
#include "Champions/Rumble.h"
#include "Champions/Ryze.h"
#include "Champions/Samira.h"
#include "Champions/Sejuani.h"
#include "Champions/Senna.h"
#include "Champions/Seraphine.h"
#include "Champions/Sett.h"
#include "Champions/Shen.h"
#include "Champions/Shyvana.h"
#include "Champions/Sion.h"
#include "Champions/Sivir.h"
#include "Champions/Skarner.h"
#include "Champions/Sona.h"
#include "Champions/Soraka.h"
#include "Champions/Swain.h"
#include "Champions/Sylas.h"
#include "Champions/Syndra.h"
#include "Champions/TahmKench.h"
#include "Champions/Taliyah.h"
#include "Champions/Talon.h"
#include "Champions/Taric.h"
#include "Champions/Thresh.h"
#include "Champions/Tristana.h"
#include "Champions/Tryndamere.h"
#include "Champions/TwistedFate.h"
#include "Champions/Twitch.h"
#include "Champions/Urgot.h"
#include "Champions/Varus.h"
#include "Champions/Velkoz.h"
#include "Champions/Vex.h"
#include "Champions/Vi.h"
#include "Champions/Viego.h"
#include "Champions/Viktor.h"
#include "Champions/Volibear.h"
#include "Champions/Warwick.h"
#include "Champions/Xayah.h"
#include "Champions/Xerath.h"
#include "Champions/XinZhao.h"
#include "Champions/Yasuo.h"
#include "Champions/Yone.h"
#include "Champions/Yorick.h"
#include "Champions/Zac.h"
#include "Champions/Zed.h"
#include "Champions/Zeri.h"
#include "Champions/Ziggs.h"
#include "Champions/Zilean.h"
#include "Champions/Zoe.h"
#include "Champions/Zyra.h"

void EvadeDB::initialize()
{
	Aatrox::load(base_database);
	Ahri::load(base_database);
	Akali::load(base_database);
	Akshan::load(base_database);
	Alistar::load(base_database);
	Amumu::load(base_database);
	Anivia::load(base_database);
	Annie::load(base_database);
	Aphelios::load(base_database);
	Ashe::load(base_database);
	AurelionSol::load(base_database);
	Azir::load(base_database);
	Bard::load(base_database);
	BelVeth::load(base_database);
	Blitzcrank::load(base_database);
	Brand::load(base_database);
	Braum::load(base_database);
	Caitlyn::load(base_database);
	Camille::load(base_database);
	Cassiopeia::load(base_database);
	ChoGath::load(base_database);
	Corki::load(base_database);
	Darius::load(base_database);
	Diana::load(base_database);
	Draven::load(base_database);
	DrMundo::load(base_database);
	Ekko::load(base_database);
	Elise::load(base_database);
	Evelynn::load(base_database);
	Ezreal::load(base_database);
	Fiddlesticks::load(base_database);
	Fiora::load(base_database);
	Fizz::load(base_database);
	Galio::load(base_database);
	Gangplank::load(base_database);
	Gnar::load(base_database);
	Graves::load(base_database);
	Gwen::load(base_database);
	Hecarim::load(base_database);
	Heimerdinger::load(base_database);
	Illaoi::load(base_database);
	Irelia::load(base_database);
	Ivern::load(base_database);
	Janna::load(base_database);
	JarvanIV::load(base_database);
	Jayce::load(base_database);
	Jhin::load(base_database);
	Jinx::load(base_database);
	Kaisa::load(base_database);
	Kalista::load(base_database);
	Karma::load(base_database);
	Karthus::load(base_database);
	Kassadin::load(base_database);
	Katarina::load(base_database);
	Kayle::load(base_database);
	Kayn::load(base_database);
	Kennen::load(base_database);
	Khazix::load(base_database);
	Kled::load(base_database);
	KogMaw::load(base_database);
	Leblanc::load(base_database);
	LeeSin::load(base_database);
	Leona::load(base_database);
	Lillia::load(base_database);
	Lissandra::load(base_database);
	Lucian::load(base_database);
	Lulu::load(base_database);
	Lux::load(base_database);
	Malphite::load(base_database);
	Malzahar::load(base_database);
	Maokai::load(base_database);
	Mordekaiser::load(base_database);
	Morgana::load(base_database);
	Nami::load(base_database);
	Nautilus::load(base_database);
	Neeko::load(base_database);
	Nidalee::load(base_database);
	Nilah::load(base_database);
	Nocturne::load(base_database);
	Olaf::load(base_database);
	Orianna::load(base_database);
	Ornn::load(base_database);
	Pantheon::load(base_database);
	Poppy::load(base_database);
	Pyke::load(base_database);
	Qiyana::load(base_database);
	Quinn::load(base_database);
	Rakan::load(base_database);
	Rammus::load(base_database);
	RekSai::load(base_database);
	Rell::load(base_database);
	Renata::load(base_database);
	Renekton::load(base_database);
	Riven::load(base_database);
	Rumble::load(base_database);
	Ryze::load(base_database);
	Samira::load(base_database);
	Sejuani::load(base_database);
	Senna::load(base_database);
	Seraphine::load(base_database);
	Sett::load(base_database);
	Shen::load(base_database);
	Shyvana::load(base_database);
	Sion::load(base_database);
	Sivir::load(base_database);
	Skarner::load(base_database);
	Sona::load(base_database);
	Soraka::load(base_database);
	Swain::load(base_database);
	Sylas::load(base_database);
	Syndra::load(base_database);
	TahmKench::load(base_database);
	Taliyah::load(base_database);
	Talon::load(base_database);
	Taric::load(base_database);
	Thresh::load(base_database);
	Tristana::load(base_database);
	Tryndamere::load(base_database);
	TwistedFate::load(base_database);
	Twitch::load(base_database);
	Urgot::load(base_database);
	Varus::load(base_database);
	Veigar::load(base_database);
	Velkoz::load(base_database);
	Vex::load(base_database);
	Vi::load(base_database);
	Viego::load(base_database);
	Viktor::load(base_database);
	Volibear::load(base_database);
	Warwick::load(base_database);
	Xayah::load(base_database);
	Xerath::load(base_database);
	XinZhao::load(base_database);
	Yasuo::load(base_database);
	Yone::load(base_database);
	Yorick::load(base_database);
	Zac::load(base_database);
	Zed::load(base_database);
	Zeri::load(base_database);
	Ziggs::load(base_database);
	Zilean::load(base_database);
	Zoe::load(base_database);
	Zyra::load(base_database);

	for (const auto& hero : entities->get_heroes())
	{
		//if (!hero->is_enemy())
		//	continue;

		for (const auto& spell : base_database)
		{
			if (spell->hero_hash == hero->get_character_hash())
			{
				database.push_back(spell);
				console->log("Added %s | hash: 0x%X", spell->menu_name, spell->spell_hashes.empty() ? 0x0 : spell->spell_hashes[0]);
			}
		}
	}

	for (const auto& spell : base_database)
	{
		if (!vector_contains(database, spell))
			delete spell;
	}
	base_database.clear();
}

EvadeSpellData* EvadeDB::get_data(const uint32_t spell_hash)
{
	for (const auto& spell : database)
	{
		if (vector_contains(spell->spell_hashes, spell_hash))
			return spell;
	}

	return nullptr;
}

EvadeSpellData* EvadeDB::get_data(const std::string& obj_name)
{
	for (const auto& spell : database)
	{
		for (const auto& name : spell->object_names)
		{
			if (obj_name.find(name) != std::string::npos)
				return spell;
		}
	}

	return nullptr;
}

void EvadeDB::on_unload()
{
	for (const auto& spell : database)
		delete spell;

	database.clear();
}