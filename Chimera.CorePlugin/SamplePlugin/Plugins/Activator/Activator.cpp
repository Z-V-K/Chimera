#include "Activator.h"

#include "ActivatorMisc.h"
#include "ActivatorPotions.h"
#include "AutoSmite.h"
#include "DefensiveItems.h"
#include "OffensiveItems.h"
#include "SummonerSpells.h"

void Activator::initialize()
{
	Menu::main_menu = menu_manager->create_menu("activator", "Activator");

	const auto summoner_spell1 = local_player->get_spell(SlotId::Summoner1);
	const auto summoner_spell2 = local_player->get_spell(SlotId::Summoner2);
	if (summoner_spell1->get_spell_data()->get_spell_name().find("Smite") != std::string::npos)
		AutoSmite::get().initialize(summoner_spell1);
	if (summoner_spell2->get_spell_data()->get_spell_name().find("Smite") != std::string::npos)
		AutoSmite::get().initialize(summoner_spell2);

	SummonerSpells::get().initialize();
	DefensiveItems::get().initialize();
	OffensiveItems::get().initialize();
	Potions::get().initialize();
	Misc::get().initialize();
}