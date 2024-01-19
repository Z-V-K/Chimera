#include "OffensiveItems.h"
#include "Activator.h"

namespace Activator
{
	void OffensiveItems::initialize()
	{
		Menu::offensive_items = Menu::main_menu->add_menu("offensive_items", "Offensive items", ICON_FA_SWORDS);
		enable = Menu::offensive_items->add_checkbox("enable", "Enable", true);
		Menu::offensive_items->set_enabled(enable);
	}

	void OffensiveItems::on_unload()
	{
		
	}

}