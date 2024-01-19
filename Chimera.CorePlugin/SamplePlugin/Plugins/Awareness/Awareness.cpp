#include "Awareness.h"

void Awareness::initialize()
{
	Menu::main_menu				= menu_manager->create_menu("awareness", "Awareness", ICON_FA_EYE);
	Menu::tab_spell_tracker		= Menu::main_menu->add_menu("spellTracker", "Spell Tracker", ICON_FA_MAGIC);
	Menu::tab_jungle_tracker	= Menu::main_menu->add_menu("jungleTracker", "Jungle Tracker", ICON_FA_TREE);
	Menu::tab_ward_tracker		= Menu::main_menu->add_menu("wardTracker", "Ward Tracker", ICON_FA_LOW_VISION);
	Menu::tab_range_indicator	= Menu::main_menu->add_menu("indicators", "Range Indicators", ICON_FA_PEOPLE_ARROWS);
	Menu::tab_waypoints			= Menu::main_menu->add_menu("waypoints", "Waypoints", ICON_FA_FLAG_ALT);
	Menu::tab_hud				= Menu::main_menu->add_menu("hud", "HUD");
	Menu::tab_champion_tracker	= Menu::main_menu->add_menu("championTracker", "Champion Tracker", ICON_FA_LAUGH);
	Menu::tab_stasis_tracker	= Menu::main_menu->add_menu("stasisTracker", "Stasis Tracker", ICON_FA_STOPWATCH);
	Menu::tab_item_tracker		= Menu::main_menu->add_menu("itemTracker", "Item Tracker", ICON_FA_TOOLS);
	Menu::tab_notifications		= Menu::main_menu->add_menu("notifications", "Notifications", ICON_FA_ENVELOPE);
}
