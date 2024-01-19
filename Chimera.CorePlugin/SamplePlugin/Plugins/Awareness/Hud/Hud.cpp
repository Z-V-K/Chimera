#include "HUD.h"

#pragma region texture_atlas
Texture* atlas_aphelios;
Texture* atlas_hud;
Texture* atlas_deathrecap;
Texture* atlas_aphelios_ability;
Vec2 size_atlas_aphelios			= { 1024.0f,  512.0f };
Vec2 size_atlas_hud					= { 1024.0f, 1024.0f };
Vec2 size_atlas_deathrecap			= { 1024.0f,  512.0f };
Vec2 size_atlas_aphelios_ability	= { 1024.0f, 1024.0f };
#pragma endregion

#pragma region uv_mapping
Vec2 uv_min_main_body		= {  15.0f / 1024.0f, 506.0f /  512.0f };
Vec2 uv_max_main_body		= { 176.0f / 1024.0f, 339.0f /  512.0f };
Vec2 uv_min_spell_border	= { 137.0f / 1024.0f, 206.0f /  512.0f };
Vec2 uv_max_spell_border	= { 185.0f / 1024.0f, 254.0f /  512.0f };
Vec2 uv_min_xp_arc			= { 631.0f / 1024.0f, 989.0f / 1024.0f };
Vec2 uv_max_xp_arc			= { 679.0f / 1024.0f, 869.0f / 1024.0f };
Vec2 uv_min_xp_arc_bg		= { 729.0f / 1024.0f, 989.0f / 1024.0f };
Vec2 uv_max_xp_arc_bg		= { 777.0f / 1024.0f, 869.0f / 1024.0f };
Vec2 uv_min_white_circle	= {   9.0f / 1024.0f, 334.0f /  512.0f };
Vec2 uv_max_white_circle	= { 164.0f / 1024.0f, 489.0f /  512.0f };
#pragma endregion

#pragma region sizes
Vec2 base_resolution			= { 1920.0f, 1080.0f };
Vec2 size_main_body				= {  100.0f,  100.0f };
Vec2 size_champion_icon			= {   72.0f,   72.0f };
Vec2 size_spell_border			= {   35.0f,   35.0f };
Vec2 size_spell_icon			= {   24.0f,   24.0f };
Vec2 size_spell_background		= {   26.0f,   26.0f };
Vec2 size_xp_arc				= {   48.0f,  120.0f };
Vec2 size_white_circle			= { ((uv_max_white_circle.x - uv_min_white_circle.x) * 1024.0f) , ((uv_max_white_circle.y - uv_min_white_circle.y) * 512.0f) };
float font_size_main			= 13.0f;
float font_size_respawn_timer	= 30.0f;
#pragma endregion

#pragma region position_offsets
Vec2 position_main_body			= { 1920.0f - size_main_body.x - 10.0f, 75.0f };
Vec2 offset_champion_icon		= { 10.0f, 14.0f };
Vec2 offset_level				= { 68.0f, 11.0f };
Vec2 offset_spell_border_one	= { 16.0f, -5.0f };
Vec2 offset_spell_border_two	= { -12.5f, 15.0f };
Vec2 offset_spell_border_three	= { -12.5f, 50.0f };
Vec2 offset_spell_icon			= { 5.0f, 5.0f };
Vec2 offset_tracker				= { 0.0f,  size_main_body.y + 20.0f };
Vec2 offset_xp_arc				= { 66.0f, 22.0f };
Vec2 offset_hp					= { 16.0f, 72.5f };
Vec2 offset_mana				= { 51.0f, 72.5f };
Vec2 offset_white_circle		= { 5.0f, 5.0f };
#pragma endregion

#pragma region scalings
float scaling_xp_arc		= 1.7f;
float scaling_white_circle	= 1.4f;
#pragma endregion

#pragma region champion_hashes
std::set<CharacterHash> energy_champions = {
	CharacterHash::Akali,
	CharacterHash::Kennen,
	CharacterHash::LeeSin,
	CharacterHash::Zed,
	CharacterHash::Shen
};

std::set<CharacterHash> manaless_champions = {
	CharacterHash::Aatrox,
	CharacterHash::Belveth,
	CharacterHash::Briar,
	CharacterHash::DrMundo,
	CharacterHash::Garen,
	CharacterHash::Gnar,
	CharacterHash::Kled,
	CharacterHash::Mordekaiser,
	CharacterHash::RekSai,
	CharacterHash::Renekton,
	CharacterHash::Rengar,
	CharacterHash::Riven,
	CharacterHash::Rumble,
	CharacterHash::Sett,
	CharacterHash::Shyvana,
	CharacterHash::Tryndamere,
	CharacterHash::Viego,
	CharacterHash::Vladimir,
	CharacterHash::Yasuo,
	CharacterHash::Yone,
	CharacterHash::Zac
};
#pragma endregion

#pragma region colors
Color col_mana		= {  11,  88, 180, 255 };
Color col_energy	= { 173, 143,  11, 255 };
Color col_hp		= {   0, 178,   2, 255 };
#pragma endregion

void Awareness::Hud::initialize()
{
	init_menu();

	atlas_aphelios			= renderer->get_texture_from_game("assets/ux/champions/aphelios/aphelios_hudatlas.tex");
	atlas_hud				= renderer->get_texture_from_game("assets/ux/lol/clarity_hudatlas.tex");
	atlas_deathrecap		= renderer->get_texture_from_game("assets/ux/deathrecap/deathrecapatlas.tex");
	atlas_aphelios_ability	= renderer->get_texture_from_game("assets/ux/champions/aphelios/aphelios_abilityatlas.tex");

	callbacks<EventType::OnDraw>::add_callback(on_draw, "Hud");
}

void Awareness::Hud::init_menu()
{
	Menu::show_hud =  Awareness::Menu::tab_hud->add_checkbox("hud_show", "Show HUD", true);
}

void Awareness::Hud::on_slow_tick()
{
}

void Awareness::Hud::on_draw()
{
	if (!Menu::show_hud->get_bool())
		return;

	int i = 0;
	for (const auto& hero : entities->get_heroes())
	{
		if (hero->is_enemy())
		{
			const Vec2 current_position_main_body = position_main_body + (offset_tracker * i);

			draw_xp_arc(current_position_main_body, hero);
			draw_base(current_position_main_body, hero);
			draw_spells(current_position_main_body, hero, SlotId::R);
			draw_spells(current_position_main_body, hero, SlotId::Summoner1);
			draw_spells(current_position_main_body, hero, SlotId::Summoner2);
			draw_hp(current_position_main_body, hero);
			draw_mana(current_position_main_body, hero);

			++i;
		}
	}
}

void Awareness::Hud::draw_base(const Vec2& offset,  GameObject* enemy)
{	
	Vec2 textSize;
	Vec2 center;
	Vec2 middle;

	draw_manager->texture(enemy->get_circle_icon(), offset + offset_champion_icon, size_champion_icon);
	
	if (enemy->get_remaining_respawn_time() > 0)
	{
		std::string respawn_time = std::to_string(static_cast<int>(std::round(enemy->get_remaining_respawn_time())));
		textSize = draw_manager->calc_text_size(respawn_time, font_size_respawn_timer);
		center = offset + offset_champion_icon + (size_champion_icon / 2);
		middle = { center.x - (textSize.x / 2) , center.y - (textSize.y / 2) };

		draw_manager->screen_circle(offset + offset_champion_icon + (size_champion_icon / 2), size_champion_icon.x / 2, Colors::SpellTracker::drop_shadow, 1.0, true);
		draw_manager->screen_text(middle, respawn_time, Color{ 220, 220, 220, 255 }, font_size_respawn_timer);
	}

	draw_manager->texture(atlas_aphelios, offset, size_main_body, 0.0f, Color{ 255, 255, 255, 255 }, uv_min_main_body, uv_max_main_body);

	std::string level = std::to_string(enemy->get_level());
	textSize = draw_manager->calc_text_size(level, font_size_main);
	middle = { offset.x + offset_level.x - (textSize.x / 2) , offset.y + offset_level.y };
	draw_manager->screen_text(middle, level, Color{ 220, 220, 220, 255 }, font_size_main);
}

void Awareness::Hud::draw_spells(const Vec2& offset, GameObject* enemy, const SlotId spell_slot_id)
{
	Vec2 position;

	switch (spell_slot_id)
	{
	case SlotId::R:
		position = offset_spell_border_one;
		break;
	case SlotId::Summoner1:
		position = offset_spell_border_two;
		break;
	case SlotId::Summoner2:
		position = offset_spell_border_three;
		break;
	default:
		return;
	}

	const auto& spell_slot = enemy->get_spell(spell_slot_id);

	draw_manager->screen_circle(offset + position + offset_spell_icon + (size_spell_background / 2), size_spell_background.x / 2, Colors::SpellTracker::Modern::background, 1.0f, true);
	draw_manager->texture(atlas_aphelios, offset + position, size_spell_border, 0.0f, Color{ 255, 255, 255, 255 }, uv_min_spell_border, uv_max_spell_border);

	if (!enemy->is_practice_tool_dummy())
	{
		draw_manager->texture(spell_slot->get_icon(), offset + position + offset_spell_icon + 1.0f, size_spell_icon, size_spell_icon.x, Color{ 255, 255, 255, 255 });
	}

	if (spell_slot->get_cooldown() > 0)
	{
		std::string cd = std::to_string(static_cast<int>(std::round(spell_slot->get_cooldown())));
		Vec2 textSize = draw_manager->calc_text_size(cd, font_size_main);
		Vec2 middle = { offset.x + position.x + offset_spell_icon.x + (size_spell_background / 2).x - (textSize.x / 2) , offset.y + position.y + offset_spell_icon.y + (size_spell_background / 2).y - (textSize.y / 2) };
		
		draw_manager->screen_circle(offset + position + offset_spell_icon + (size_spell_background / 2), size_spell_background.x / 2, Colors::SpellTracker::drop_shadow, 1.0f, true);
		draw_manager->screen_text(middle, cd, Color{ 220, 220, 220, 255 }, font_size_main);
	}
}

void Awareness::Hud::draw_hp(const Vec2& offset, GameObject* enemy)
{
	Vec2 new_uv_min;
	Vec2 displacement;
	Vec2 new_size;

	float percentage_hp = enemy->get_health() / enemy->get_max_health();

	draw_manager->screen_circle(offset + offset_hp + offset_spell_icon + (size_spell_background / 2), size_spell_background.x / 2, Colors::SpellTracker::Modern::background, 1.0f, true);

	if (percentage_hp > 0.0f)
	{
		new_uv_min		= { uv_min_white_circle.x , (334.0f + ((1 - percentage_hp) * size_white_circle.y)) / 512.f };
		displacement	= { 0.0f,  ((1 - percentage_hp) * size_spell_border.y) / scaling_white_circle };
		new_size		= { size_spell_border.x / scaling_white_circle, (size_spell_border.y * percentage_hp) / scaling_white_circle };

		draw_manager->texture(atlas_deathrecap, offset + offset_hp + offset_white_circle + displacement, new_size, 0.0f, col_hp, new_uv_min, uv_max_white_circle);
	}

	draw_manager->texture(atlas_aphelios, offset + offset_hp, size_spell_border, 0.0f, Color{ 255, 255, 255, 255 }, uv_min_spell_border, uv_max_spell_border);

	std::string hp = std::to_string(static_cast<int>(percentage_hp * 100));
	Vec2 text_size_hp = draw_manager->calc_text_size(hp, font_size_main);
	Vec2 middle_hp = { offset.x + offset_hp.x + offset_spell_icon.x + (size_spell_background / 2).x - (text_size_hp.x / 2) , offset.y + offset_hp.y + offset_spell_icon.y + (size_spell_background / 2).y - (text_size_hp.y / 2) };
	draw_manager->screen_text(middle_hp, hp, Color{ 220, 220, 220, 255 }, font_size_main);
}

void Awareness::Hud::draw_mana(const Vec2& offset, GameObject* enemy)
{
	Vec2 new_uv_min;
	Vec2 displacement;
	Vec2 new_size;
	const auto& enemy_hash = enemy->get_character_hash();
	Color mana_energy = energy_champions.contains(enemy_hash) ? col_energy : col_mana;

	draw_manager->screen_circle(offset + offset_mana + offset_spell_icon + (size_spell_background / 2), size_spell_background.x / 2, Colors::SpellTracker::Modern::background, 1.0f, true);

	if (!manaless_champions.contains(enemy_hash))
	{
		float percentage_mana = enemy->get_mana() / enemy->get_max_mana();

		if (percentage_mana > 0.0f)
		{
			new_uv_min = { uv_min_white_circle.x , (334.0f + ((1 - percentage_mana) * size_white_circle.y)) / 512.f };
			displacement = { 0.0f,  ((1 - percentage_mana) * size_spell_border.y) / scaling_white_circle };
			new_size = { size_spell_border.x / scaling_white_circle, (size_spell_border.y * percentage_mana) / scaling_white_circle };

			draw_manager->texture(atlas_deathrecap, offset + offset_mana + offset_white_circle + displacement, new_size, 0.0f, mana_energy, new_uv_min, uv_max_white_circle);
		}

		std::string mana = std::to_string(static_cast<int>(percentage_mana * 100));
		Vec2 text_size_mana = draw_manager->calc_text_size(mana, font_size_main);
		Vec2 middle_mana = { offset.x + offset_mana.x + offset_spell_icon.x + (size_spell_background / 2).x - (text_size_mana.x / 2) , offset.y + offset_mana.y + offset_spell_icon.y + (size_spell_background / 2).y - (text_size_mana.y / 2) };

		draw_manager->screen_text(middle_mana, mana, Color{ 220, 220, 220, 255 }, font_size_main);
	}

	draw_manager->texture(atlas_aphelios, offset + offset_mana, size_spell_border, 0.0f, Color{ 255, 255, 255, 255 }, uv_min_spell_border, uv_max_spell_border);
}

void Awareness::Hud::draw_xp_arc(const Vec2& offset, GameObject* enemy)
{
	Vec2 size = { ((uv_max_xp_arc.x - uv_min_xp_arc.x) * 1024.0f) / scaling_xp_arc, ((uv_min_xp_arc.y - uv_max_xp_arc.y) * 1024.0f) / scaling_xp_arc };
	draw_manager->texture(atlas_hud, offset + offset_xp_arc, size, 0.0f, Color{ 255, 255, 255, 255 }, uv_min_xp_arc_bg, uv_max_xp_arc_bg);

	float current_xp = enemy->get_accumulated_experience();
	int lower_xp_bound = get_xp_lower_bound(enemy->get_level());
	int higher_xp_bound = get_xp_higher_bound(enemy->get_level());
	float percentage_xp_for_next_level = (current_xp - lower_xp_bound) / (higher_xp_bound - lower_xp_bound);

	if(percentage_xp_for_next_level <= 0.0f || percentage_xp_for_next_level >= 1.0f) return;

	Vec2 new_uv_min_xp_arc = { uv_min_xp_arc.x, (869.0f + percentage_xp_for_next_level * (size.y * scaling_xp_arc)) / 1024.f };
	Vec2 displacement = { 0.0f, size.y - (percentage_xp_for_next_level * size.y)};
	Vec2 newSize = { size.x, size.y * percentage_xp_for_next_level };

	draw_manager->texture(atlas_hud, offset + offset_xp_arc + displacement, newSize, 0.0f, Color{ 255, 255, 255, 255 }, new_uv_min_xp_arc, uv_max_xp_arc);
}

int Awareness::Hud::get_xp_lower_bound(int level)
{
	if (level == 1)
		return 0;

	int total_xp = 280;

	for (int i = 2; i < level; i++)
	{
		total_xp += (i + 1) * 100 + 80;
	}

	return total_xp;
}

int Awareness::Hud::get_xp_higher_bound(int level)
{
	if (level == 1)
		return 280;

	int total_xp = 280;

	for (int i = 2; i <= level; i++)
	{
		total_xp += (i + 1) * 100 + 80;
	}

	return total_xp;
}