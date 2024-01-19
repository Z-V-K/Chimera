#include "NotificationSystem.h"

std::list<Awareness::NotificationSystem::Notification*> notification_list;
Vec2 size_accent_left = { 50.0f, 50.0f };
Vec2 size_announcement = { 350.0f, 50.0f };
Vec2 margin_announcements = { 0.0f, -70.0f };
Vec2 padding_announcements = { 5.0f, 0.0f };
Vec2 padding_announcement_icon = { 10.0f, 5.0f };
Vec2 padding_annoucement_text = { 40.0f, 0.0f };
Vec2 size_announcement_icon = { 40.0f, 40.0f };
float radius_corner = 10.0f;
float announcement_font_size = 16.0f;

Texture* epic_monsters_atlas;
Awareness::NotificationSystem::Notification test_notification;

void Awareness::NotificationSystem::initialize()
{
	Menu::announcements				= Awareness::Menu::tab_notifications->add_menu("announcements", "Announcements", ICON_FA_ENVELOPE_OPEN);
	Menu::show_announcements		= Menu::announcements->add_checkbox("show_announcements", "Show Announcements", true);
	Menu::pos_x_announcements		= Menu::announcements->add_slider("announcements_pos_x", "Position X", 50, 0, 1920);
	Menu::pos_y_announcements		= Menu::announcements->add_slider("announcements_pos_y", "Position Y", 500, 0, 1080);

	Menu::hyper_notifications		= Awareness::Menu::tab_notifications->add_menu("hyper_notifications", "Hyper Notifications", ICON_FA_ALARM_EXCLAMATION);
	Menu::show_hyper_notifications	= Menu::hyper_notifications->add_checkbox("show_hyper_notifications", "Show Hyper-Notifications", true);
	Menu::pos_x_hyper_notifications = Menu::hyper_notifications->add_slider("hyper_notifications_pos_x", "Position X", 1800, 0, 1920);
	Menu::pos_y_hyper_notifications = Menu::hyper_notifications->add_slider("hyper_notifications_pos_y", "Position Y", 500, 0, 1080);

	epic_monsters_atlas = renderer->get_texture_from_game("assets/ux/lol/objectivealignment_atlas.tex");
	std::vector<std::pair<std::string, Color>> blub = 
	{ 
		{ "ELDER DRAGON  ",     Color { 255,  95,  31, 255} },
		{ "is under attack!",   Color  {255, 255, 255, 255} }
	};
	Vec2 bl{ 284.0f / 512.0f, 164.0f / 512.0f };
	Vec2 bz{ 351.0f / 512.0f, 231.0f / 512.0f };

	test_notification = Awareness::NotificationSystem::create_notification(Awareness::NotificationSystem::Notification_Type::Announcement, 10.0f, blub, epic_monsters_atlas, bl, bz);
	Awareness::NotificationSystem::push_custom_notification(&test_notification);	
	Awareness::NotificationSystem::push_custom_notification(&test_notification);

	callbacks<EventType::OnDraw>::add_callback(on_draw, "NotificationSystem");
	callbacks<EventType::OnSlowTick>::add_callback(on_slow_tick, "NotificationSystem");
}

void Awareness::NotificationSystem::on_draw()
{
	Vec2 root_pos_announcements = 
	{ 
		(float)Menu::pos_x_announcements->get_int(),  
		(float)Menu::pos_y_announcements->get_int()
	};

	if (Menu::show_announcements->get_bool())
	{
		int  i = 0;
		for (auto notification = notification_list.rbegin(); notification != notification_list.rend(); ++notification)
		{
			Vec2 position_accent_left =
			{
				root_pos_announcements.x + i * margin_announcements.x,
				root_pos_announcements.y + i * margin_announcements.y
			};

			draw_manager->screen_rectangle(position_accent_left, position_accent_left + size_accent_left, Colors::Notifications::accent, radius_corner, 1.0f, true);
			draw_manager->screen_rectangle(position_accent_left + padding_announcements, position_accent_left + size_announcement - padding_announcements, Colors::Notifications::background, radius_corner, 1.0f, true);
			draw_manager->screen_circle(position_accent_left + padding_announcements + padding_announcement_icon + size_announcement_icon / 2, (size_announcement_icon.x / 2) + 2.0f, Colors::Notifications::icon_shadow, 1.0f, true);
			draw_manager->texture(epic_monsters_atlas, position_accent_left + padding_announcements + padding_announcement_icon, size_announcement_icon, 20.0f, Color{ 255, 255, 255, 255 }, (*notification)->uv_min, (*notification)->uv_max);

			float current_text_width = 0.0f;

			for (int m = 0; m < (*notification)->content.size(); ++m)
			{
				Vec2 text_size = draw_manager->calc_text_size((*notification)->content[m].first, announcement_font_size);
				Vec2 root_text = position_accent_left + padding_announcements + padding_announcement_icon + size_announcement_icon / 2 + padding_annoucement_text;
				root_text.x += current_text_width;
				root_text.y -= text_size.y / 2;
				current_text_width += text_size.x;

				draw_manager->screen_text(root_text, (*notification)->content[m].first, (*notification)->content[m].second, announcement_font_size);
			}

			++i;
		}
	}

	if (Menu::show_hyper_notifications->get_bool())
	{

	}
}


void Awareness::NotificationSystem::on_slow_tick()
{
	for (auto notification = notification_list.begin(); notification != notification_list.end(); ++notification)
	{
		float time_passed = game_time->get_time() - (*notification)->creation_timestamp;

		if (time_passed > (*notification)->duration)
			notification_list.erase(notification);
	}
}

void Awareness::NotificationSystem::push_custom_notification(Notification* notification)
{
	if (!notification) return;

	notification->creation_timestamp = game_time->get_time();

	notification_list.emplace_back(notification);
}

Awareness::NotificationSystem::Notification Awareness::NotificationSystem::create_notification(Notification_Type type, float visible_duration, std::vector<std::pair<::std::string, Color>>& text_data, Texture* texture, Vec2& uv_min, Vec2& uv_max)
{
	Awareness::NotificationSystem::Notification temp;

	temp.notification_type	= type;
	temp.duration			= visible_duration;
	temp.content			= text_data;
	temp.icon				= texture;
	temp.uv_min				= uv_min;
	temp.uv_max				= uv_max;

	return temp;
}