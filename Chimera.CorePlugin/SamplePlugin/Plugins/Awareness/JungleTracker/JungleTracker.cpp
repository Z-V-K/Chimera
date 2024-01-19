#include "JungleTracker.h"

// object ->	CampRespawn					| 0x3101C878
// buff	  ->	camprespawncountdownhidden  | 0xAD1E78D3 (first)
// buff   ->	camprespawncountdownvisible | 0xE2B233B7 (second)

bool once = true;

void Awareness::JungleTracker::initialize()
{
	Color white = { 255, 255, 255, 255 };

	Menu::general_settings		= Awareness::Menu::tab_jungle_tracker->add_menu("mgJungleTrackerGeneral", "General Settings", ICON_FA_COGS);
	Menu::alerts				= Awareness::Menu::tab_jungle_tracker->add_menu("mgJungleTrackerAlert", "Notification Settings", ICON_FA_BELL_EXCLAMATION);
	Menu::show_timer_world		= Menu::general_settings->add_checkbox("meShowJungleTimerWorld", "Show Timers on World", true);
	Menu::show_camp_outline		= Menu::general_settings->add_checkbox("show_camp_outline", "Highlight Camp Outline", true);
	Menu::show_camp_outline_color = Menu::general_settings->add_colorpick("show_camp_outline_color", "^- Color", white);
	Menu::show_timer_hud		= Menu::general_settings->add_checkbox("meShowJungleTimerHud", "Show Timers on HUD", false);
	Menu::show_timer_minimap	= Menu::general_settings->add_checkbox("meShowTimersMinimap", "Show Timers on Minimap", true);

	callbacks<EventType::OnDraw>::add_callback(on_draw, "JungleTracker");
	callbacks<EventType::OnDrawEnvironment>::add_callback(on_draw_environment, "JungleTracker");
	callbacks<EventType::OnSlowTick>::add_callback(on_slow_tick, "JungleTracker");
	callbacks<EventType::OnPlayAnimation>::add_callback(on_play_animation, "JungleTracker");
	callbacks<EventType::OnCreateObject>::add_callback(on_create_object, "JungleTracker");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete_object, "JungleTracker");
	callbacks<EventType::OnNotifyEvent>::add_callback(on_notify_event, "JungleTracker");
}

void Awareness::JungleTracker::on_draw()
{
	// draw minimap + hud tracker here
}

void Awareness::JungleTracker::on_draw_environment()
{
	// only draw campoutline + world tracker here so they dont overlap
}

void Awareness::JungleTracker::on_slow_tick()
{
	// manage minion list
}

void Awareness::JungleTracker::on_play_animation(GameObject* sender, const std::string& animation_name, uint32_t animation_hash, bool* process)
{
}

void Awareness::JungleTracker::on_create_object(GameObject* obj)
{
}

void Awareness::JungleTracker::on_delete_object(GameObject* obj)
{
}

void Awareness::JungleTracker::on_notify_event(GameObject* source, const char* event_name, int event_id)
{
	if (!source) 
		return;

	console->log("EVENT: %s | %s | %i", source->get_name().c_str(), event_name, event_id);
}
