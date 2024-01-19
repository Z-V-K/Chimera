#include "../Colors.h"
#include "../Awareness.h"

#pragma once
namespace Awareness::NotificationSystem
{
	namespace Menu
	{
		inline MenuTab*  announcements;
		inline MenuItem* show_announcements;
		inline MenuItem* pos_x_announcements;
		inline MenuItem* pos_y_announcements;

		inline MenuTab*  hyper_notifications;
		inline MenuItem* show_hyper_notifications;
		inline MenuItem* pos_x_hyper_notifications;
		inline MenuItem* pos_y_hyper_notifications;
	}

	enum Notification_Type { Announcement, Hyper };
	struct Notification
	{
		Notification_Type notification_type;
		std::vector<std::pair<::std::string, Color>> content;
		float duration;
		float creation_timestamp;
		Texture* icon;
		Vec2 uv_min;
		Vec2 uv_max;
	};

	static void on_draw();
	static void on_slow_tick();
	void initialize();
	void push_custom_notification(Notification* notification);
	Notification create_notification(Notification_Type type, float visible_duration, std::vector<std::pair<::std::string, Color>>& text_data, Texture* texture, Vec2& uv_min, Vec2& uv_max);
};