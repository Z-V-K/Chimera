#include "DefensiveItems.h"
#include "Activator.h"

namespace Activator
{
	void DefensiveItems::initialize()
	{
		Menu::defensive_items = Menu::main_menu->add_menu("defensive_items", "Defensive items", ICON_FA_SHIELD_ALT);
		enable = Menu::defensive_items->add_checkbox("enable", "Enable", true);
		Menu::defensive_items->set_enabled(enable);
	}

	void DefensiveItems::on_unload()
	{
		
	}

}