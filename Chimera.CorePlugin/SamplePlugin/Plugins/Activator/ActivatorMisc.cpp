#include "ActivatorMisc.h"
#include "Activator.h"

namespace Activator
{
	void Misc::initialize()
	{
		Menu::misc = Menu::main_menu->add_menu("misc", "Miscellaneous");
		enable = Menu::misc->add_checkbox("enable", "Enable", true);
		Menu::misc->set_enabled(enable);
	}

	void Misc::on_unload()
	{
		
	}

}