#include "../Awareness.h"
#include "../NotificationSystem/NotificationSystem.h"

#pragma once

namespace Awareness::JungleTracker
{
	namespace Menu
	{
		inline MenuTab* general_settings{};
		inline MenuTab* alerts{};
		inline MenuItem* show_timer_minimap{};
		inline MenuItem* show_timer_world{};
		inline MenuItem* show_timer_hud{};
		inline MenuItem* show_camp_outline{};
		inline MenuItem* show_camp_outline_color{};
	}

	static void on_draw();
	static void on_draw_environment();
	static void on_slow_tick();
	static void on_play_animation(GameObject* sender, const std::string& animation_name, uint32_t animation_hash, bool* process);
	static void on_create_object(GameObject* obj);
	static void on_delete_object(GameObject* obj);
	static void on_notify_event(GameObject* source, const char* event_name, int event_id);
	void initialize();
};

