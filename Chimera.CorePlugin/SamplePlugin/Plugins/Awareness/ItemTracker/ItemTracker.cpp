#include "ItemTracker.h"

std::set<ItemId> active_items = {
	ItemId::Stopwatch,
	ItemId::Ironspike_Whip,
	ItemId::Quicksilver_Sash,
	ItemId::Redemption,
	ItemId::Mikaels_Blessing,
	ItemId::Randuins_Omen,
	ItemId::Turbo_Chemtank,
	ItemId::Edge_of_Night,
	ItemId::Zhonyas_Hourglass,
	ItemId::Immortal_Shieldbow,
	ItemId::Mercurial_Scimitar,
	ItemId::Guardian_Angel,
	ItemId::Silvermere_Dawn,
	ItemId::Steraks_Gage,
	ItemId::Gargoyle_Stoneplate,
	ItemId::Blade_of_the_Ruined_King,
	ItemId::Shurelyas_Battlesong,
	ItemId::Locket_of_the_Iron_Solari,
	ItemId::Crown_of_the_Shattered_Queen,
	ItemId::Everfrost,
	ItemId::Youmuus_Ghostblade,
	ItemId::Duskblade_of_Draktharr,
	ItemId::Ludens_Tempest,
	ItemId::Hextech_Rocketbelt,
	ItemId::Goredrinker,
	ItemId::Stridebreaker,
	ItemId::Galeforce
};

Vec2 offset_healthbar = { -100.0f, -27.5f };
Vec2 texture_size = { 25.0f, 25.0f };
float background_shadow_radius = 14.0f;
float it_font_size = 12.0f;

std::vector<Vec2> grid_offsets = {
	{    0.0f,    0.0f},
	{ - 30.0f,    0.0f},
	{    0.0f, - 30.0f},
	{ - 30.0f, - 30.0f},
	{    0.0f, - 60.0f},
	{ - 30.0f, - 60.0f},

};

void Awareness::ItemTracker::initialize()
{
	Menu::item_tracker_myself = Awareness::Menu::tab_item_tracker->add_checkbox("itemTrackerMyself", "Myself", true);
	Menu::item_tracker_allies = Awareness::Menu::tab_item_tracker->add_checkbox("itemTrackerAllies", "Allies", true);
	Menu::item_tracker_enemies = Awareness::Menu::tab_item_tracker->add_checkbox("itemTrackerEnemies", "Enemies", true);

	callbacks<EventType::OnDraw>::add_callback(on_draw, "ItemTracker");
}

void Awareness::ItemTracker::on_draw()
{
	for (const auto& hero : entities->get_heroes())
	{
		if (!hero || hero->is_clone() || !hero->is_alive()) return;

		if (Menu::item_tracker_enemies->get_bool() && !hero->is_ally())
			draw_items(hero);

		if (Menu::item_tracker_allies->get_bool() && hero->is_ally())
		{
			if (hero == local_player && !Menu::item_tracker_myself->get_bool()) continue;
			draw_items(hero);
		}
	}

}

void Awareness::ItemTracker::draw_items(GameObject* hero)
{
	std::vector<InventoryItem*> items_to_draw;

	for (const auto& hero_item : hero->get_items())
	{
		if (!hero_item) return;

		ItemId itemId = hero_item->get_item_id();
		auto find = active_items.find(itemId);

		if (find != active_items.end())
			items_to_draw.push_back(hero_item);
	}

	for (size_t i = 0; i < items_to_draw.size(); i++)
	{
		ItemTexture item_texture = items_to_draw[i]->get_icon();
		Texture* atlas = item_texture.texture;
		Vec2 uv_min = item_texture.get_uv_min();
		Vec2 uv_max = item_texture.get_uv_max();
		Vec2 root_healthbar = hero->get_health_bar_screen_position() + offset_healthbar + grid_offsets[i];

		draw_manager->screen_circle(root_healthbar + texture_size / 2, background_shadow_radius, Color{ 0, 0, 0, 100 }, 1.0f, true);
		draw_manager->texture(atlas, root_healthbar, texture_size, 20.0f, hero->is_invulnerable() ? Colors::SpellTracker::stasis : Color{255,255,255,255}, uv_min, uv_max);

		float item_cooldown = hero->get_item_spell_slot(items_to_draw[i]->get_item_id())->get_cooldown();

		if (item_cooldown > 0.0f)
		{
			char s_remaining_cooldown[125];
			sprintf(s_remaining_cooldown, "%.0f", item_cooldown);

			Vec2 middle = { root_healthbar.x + (texture_size.x / 2) , root_healthbar.y + (texture_size.x / 2) };
			Vec2 text_size = draw_manager->calc_text_size(s_remaining_cooldown, it_font_size);
			Vec2 text_middle = middle - (text_size / 2);

			draw_manager->screen_circle(middle, texture_size.x / 2, Colors::SpellTracker::drop_shadow, 1.0f, true);
			draw_manager->screen_text(text_middle, s_remaining_cooldown, Colors::SpellTracker::Legacy::cooldown_font, it_font_size);
		}
	}
}
