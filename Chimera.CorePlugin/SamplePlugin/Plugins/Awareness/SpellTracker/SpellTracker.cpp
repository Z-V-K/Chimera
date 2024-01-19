#include "SpellTracker.h"

#include "../Awareness.h"
#include "../Colors.h"

#pragma region variable declaration
std::vector<std::string> designs;

std::map<std::string, std::pair<int, int>> legacyHpBarOffsetsChamps;
Vec2 legacyHpbarPosOffset;
Vec2 legacyBackgroundSize;
Vec2 legacySlotDimension;
Vec2 legacySlotOffset;
Vec2 legacyLvlIndicatorOffset;
Vec2 legacyLvlIndicatorSpacer;
Vec2 legacySumsDimensions;
Vec2 legacySumsOffset;
int  legacyLvlIndicatorSpacerSpecial;

Vec2 minimalHpBarPosOffset;
Vec2 minimalHpBarPosSize;
Vec2 minimalSlotDimension;
Vec2 minimalSlotStart;
Vec2 minimalSlotOffset;
Vec2 minimalShadowbarDimension;
Vec2 minimalShadowbarOffset;
Vec2 minimalSumsDimensions;
Vec2 minimalSumsOffset;
Vec2 minimalSumsBackgroundDimensions;
Vec2 minimalSumsBackgroundOffset;

Vec2 chimeraHpBarOffset;
Vec2 chimeraIconSize;
Vec2 chimeraSumsDimensions;
Vec2 chimeraSumsOffset;
int  chimeraShadowRadius;
#pragma endregion

std::unordered_map<GameObject*, std::array<Awareness::SpellTracker::CastedSpell, 6>> casted_spells;

void Awareness::SpellTracker::initialize()
{
	for (const auto& hero : entities->get_heroes())
	{
		if (!casted_spells.contains(hero))
		{
			casted_spells.insert({ hero, { } });
			casted_spells[hero][0].spell = hero->get_spell((SlotId) 0);
			casted_spells[hero][1].spell = hero->get_spell((SlotId) 1);
			casted_spells[hero][2].spell = hero->get_spell((SlotId) 2);
			casted_spells[hero][3].spell = hero->get_spell((SlotId) 3);
			casted_spells[hero][4].spell = hero->get_spell((SlotId) 4);
			casted_spells[hero][5].spell = hero->get_spell((SlotId) 5);

			casted_spells[hero][0].ability_haste = static_cast<float>(hero->get_ability_haste());
			casted_spells[hero][1].ability_haste = static_cast<float>(hero->get_ability_haste());
			casted_spells[hero][2].ability_haste = static_cast<float>(hero->get_ability_haste());
			casted_spells[hero][3].ability_haste = static_cast<float>(hero->get_ability_haste());
			casted_spells[hero][4].ability_haste = static_cast<float>(hero->get_ability_haste());
			casted_spells[hero][5].ability_haste = static_cast<float>(hero->get_ability_haste());
		}
	}

	#pragma region variables init
	designs = { "Legacy", "Minimal", "Chimera" };

	legacyHpBarOffsetsChamps =
	{
		{ "Aphelios",		{  5,  5 } },
		{ "Annie",			{ 10,  9 } },
		{ "Corki",			{  8,  5 } }, //todo
		{ "Gwen",			{  5, 10 } }, //todo
		{ "Irelia",			{  5, 10 } }, //todo
		{ "Jhin",			{ 10, 11 } },
		{ "Mordekaiser",	{ 10, 11 } },
		{ "Pantheon",		{ 10, 10 } },
		{ "Rengar",			{  5, 10 } }, //todo
		{ "Samira",			{ 13, 13 } },
		{ "Seraphine",		{ 10, 10 } },

		{ "Sona",			{  5, 10 } }, //todo
		{ "Vex",			{  5, 10 } }, //todo
		{ "Zeri",			{  5, 10 } }, //todo
		{ "Graves",			{  5, 10 } }, //todo
		{ "Ahri",			{ 10, 10 } },
		{ "Syndra",			{  5, 10 } }  //todo
	};

	legacyHpbarPosOffset			= {  -47,  -2 };
	legacyBackgroundSize			= {  110,  10 };
	legacySlotDimension				= {   25,   8 };
	legacySlotOffset				= {    2,   1 };
	legacyLvlIndicatorOffset		= {   -1,  -2 };
	legacyLvlIndicatorSpacer		= {    4,   4 };
	legacySumsDimensions			= {   25,  25 };
	legacySumsOffset				= { -123, -27 };
	legacyLvlIndicatorSpacerSpecial	= 3;

	minimalHpBarPosOffset				= { -88,  -3 };
	minimalHpBarPosSize					= { 151,  8 };
	minimalSlotDimension				= { 22, 5};
	minimalSlotStart					= { 38, 1 };
	minimalSlotOffset					= { 5, 1};
	minimalShadowbarOffset				= { 41, 1 };
	minimalShadowbarDimension			= { 107, 5 };
	minimalSumsDimensions				= { 15,  15 };
	minimalSumsOffset					= { -87, -27 };
	minimalSumsBackgroundOffset			= { -2, -2 };
	minimalSumsBackgroundDimensions		= { 26, 7 };

	chimeraHpBarOffset		= { -38, 8 };
	chimeraIconSize			= { 17, 17 };
	chimeraSumsDimensions	= { 17, 17 };
	chimeraSumsOffset		= { 68, -14 };
	chimeraShadowRadius		= 12.0f;

	#pragma endregion

	Menu::spell_tracker_design = Awareness::Menu::tab_spell_tracker->add_menu("mgSpellTrackerVisuals", "Visuals", ICON_FA_EYE);
	Menu::spell_tracker_design_choice = Menu::spell_tracker_design->add_combo("spell_tracker_design_choice", "Design", 2, designs);
	Menu::spell_tracker = Awareness::Menu::tab_spell_tracker->add_menu("mgSpellTrackerOptions", "Options", ICON_FA_COGS);
	Menu::spell_tracker_me = Menu::spell_tracker->add_checkbox("spell_tracker_me", "Myself", true);
	Menu::spell_tracker_enemies = Menu::spell_tracker->add_checkbox("spell_tracker_enemies", "Enemies", true);
	Menu::spell_tracker_allies = Menu::spell_tracker->add_checkbox("spell_tracker_allies", "Allies", true);
	
	callbacks<EventType::OnDraw>::add_callback(on_draw, "SpellTracker");
	callbacks<EventType::OnProcessSpellCast>::add_callback(on_process_spell_cast, "SpellTracker");
}

void Awareness::SpellTracker::draw_trackers(GameObject* entity)
{
	std::vector<SpellSlot*> slots = {
		entity->get_spell(SlotId::Q),
		entity->get_spell(SlotId::W),
		entity->get_spell(SlotId::E),
		entity->get_spell(SlotId::R),
		entity->get_spell(SlotId::Summoner1),
		entity->get_spell(SlotId::Summoner2)
	};

	if (!casted_spells.contains(entity))
	{
		casted_spells.insert({ entity, { } });
		casted_spells[entity][0].spell = slots[0];
		casted_spells[entity][1].spell = slots[1];
		casted_spells[entity][2].spell = slots[2];
		casted_spells[entity][3].spell = slots[3];
		casted_spells[entity][4].spell = slots[4];
		casted_spells[entity][5].spell = slots[5];
	}

	switch (Menu::spell_tracker_design_choice->get_int())
	{
	case 0:
		LegacyTracker::draw_spell_tracker(entity, slots);
		break;
	case 1:
		ModernTracker::draw_spell_tracker(entity, slots);
		break;
	case 2:
		ChimeraTracker::draw_spell_tracker(entity, slots);
		break;
	default:
		break;
	}
}

void Awareness::SpellTracker::on_draw()
{
	for (const auto& hero : entities->get_heroes())
	{
		if (hero->is_practice_tool_dummy()) 
			continue;

		if (hero->is_ally() && !hero->is_me() && !Menu::spell_tracker_allies->get_bool())
			continue;

		if (hero->is_enemy() && !Menu::spell_tracker_enemies->get_bool())
			continue;

		if (hero->is_me() && !Menu::spell_tracker_me->get_bool())
			continue;

		if (!hero->is_visible() || !hero->is_alive() || !hero->is_visible_on_screen() || !hero->is_valid_target(FLT_MAX, { }, true))
			continue;

		draw_trackers(hero);
		draw_xp_bar(hero);
	}
}

void Awareness::SpellTracker::on_process_spell_cast(SpellCastInfo* spell)
{
	const auto source = spell->get_source();

	if (!source)
		return;

	const auto slot = spell->get_slot();

	if (slot > SlotId::Summoner2 || slot < SlotId::Q)
		return;

	if (!casted_spells.contains(source))
	{
		casted_spells.insert({ source, { } });
		casted_spells[source][0].spell = source->get_spell((SlotId) 0);
		casted_spells[source][1].spell = source->get_spell((SlotId) 1);
		casted_spells[source][2].spell = source->get_spell((SlotId) 2);
		casted_spells[source][3].spell = source->get_spell((SlotId) 3);
		casted_spells[source][4].spell = source->get_spell((SlotId) 4);
		casted_spells[source][5].spell = source->get_spell((SlotId) 5);
	}

	casted_spells[source][(int)slot].update(static_cast<float>(source->get_ability_haste()));
}

int get_xp_lower_bound(int level)
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

int get_xp_higher_bound(int level)
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

void Awareness::SpellTracker::draw_xp_bar(GameObject* entity)
{
	const float bar_width = 105.f;
	const Vec2 start_pos = entity->get_health_bar_screen_position() - Vec2(45.f, 29.f);

	int lower_bound = get_xp_lower_bound(entity->get_level());
	int higher_bound = get_xp_higher_bound(entity->get_level());
	
	int xp_bar_width = ((entity->get_accumulated_experience() - lower_bound) * bar_width) / (higher_bound - lower_bound);

	if (entity->get_accumulated_experience() > higher_bound)
		xp_bar_width = bar_width;

	Vec2 end_pos = start_pos + Vec2(xp_bar_width, 0.f);

	draw_manager->screen_rectangle(start_pos - Vec2(0, 1.f), start_pos + Vec2(bar_width, 1.f), Colors::SpellTracker::exp_bar_bg);
	draw_manager->screen_rectangle(start_pos, end_pos, Colors::SpellTracker::exp_bar);
}

#pragma region Legacy Tracker
void Awareness::SpellTracker::LegacyTracker::draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots)
{
	bool isStasis = entity->is_invulnerable();
	Vec2 backgroundBarRoot = (entity->get_health_bar_screen_position() + legacyHpbarPosOffset);
	Vec2 backgroundBarEnd = (backgroundBarRoot + legacyBackgroundSize);

	draw_manager->screen_rectangle(backgroundBarRoot, backgroundBarEnd, Colors::SpellTracker::Legacy::background, 0.0f, 1.0f, true);
	
	int j = 0;
	for (int i = 0; i < slots.size(); i++)
	{
		const auto spell_slot = slots[i];
		const auto casted_spell = casted_spells[entity][(int)spell_slot->get_slot_id()];

		if (i > 3)
		{
			Color col{ 0, 0, 0, 255 };
			Vec2 root, end, hDisplacement;
			void* texture = spell_slot->get_icon();
			hDisplacement.x = j * legacySumsDimensions.x;
			root = entity->get_health_bar_screen_position() + legacySumsOffset + hDisplacement;
			end = root + legacySumsDimensions;

			if (!casted_spell.is_ready())
			{
				std::string cd = std::to_string(static_cast<int>(std::round(casted_spell.get_cooldown() + 1)));

				Vec2 textSize = draw_manager->calc_text_size(cd, 14);
				Vec2 middle = { root.x + 13.5f - (textSize.x / 2),
								root.y + 13.0f - (textSize.y / 2) };

				draw_manager->texture(texture, root, legacySumsDimensions, 5.0f, isStasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::dark_red);
				draw_manager->screen_text(middle, cd, Color(255, 255, 255, 255), 14);
			} else 
			{
				draw_manager->texture(texture, root, legacySumsDimensions, 5.0f, isStasis ? Colors::SpellTracker::stasis : Color{255,255,255,255});
			}

			j++;
			continue;
		}

		if (spell_slot->get_level() == 0) continue;

		Vec2 slotRoot =
		{
			backgroundBarRoot.x + ((i + 1) * legacySlotOffset.x) + (i * legacySlotDimension.x),
			legacySlotOffset.y + backgroundBarRoot.y
		};

		Vec2 slotEnd = slotRoot + legacySlotDimension;

		if (!casted_spell.is_ready())
		{
			LegacyTracker::draw_progress_bar(casted_spell, slotRoot, isStasis);
		}
		else {
			draw_manager->screen_rectangle(slotRoot, slotEnd, isStasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::Legacy::foreground, 0.0f, 1.0f, true);
			LegacyTracker::draw_level_indicator(slotRoot, spell_slot);
		}
	}
}

void Awareness::SpellTracker::LegacyTracker::draw_level_indicator(const Vec2& root, SpellSlot* spell)
{
	int spacer = legacyLvlIndicatorSpacer.x;
	if (spell->get_level() > 5) spacer = legacyLvlIndicatorSpacerSpecial;

	for (int i = 1; i <= spell->get_level(); i++)
	{
		Vec2 pos = root;
		Vec2 offset{ (float)(i * spacer), legacyLvlIndicatorSpacer.y };
		pos.x += offset.x;
		pos.y += offset.y;
		Vec2 topLeft, bottomRight;
		topLeft.x = pos.x - legacyLvlIndicatorOffset.x;
		topLeft.y = pos.y - legacyLvlIndicatorOffset.x;
		bottomRight.x = topLeft.x + legacyLvlIndicatorOffset.y;
		bottomRight.y = topLeft.y + legacyLvlIndicatorOffset.y;
		//draw_manager->screen_circle(pos, 1.5f, Menu::menuEntryDrawSpellTrackerBackgroundCol->get_color(), true);
		draw_manager->screen_rectangle(topLeft, bottomRight, Colors::SpellTracker::Legacy::level_indicator_dot, 0.0f, 1.0f, true);
	}
}

void Awareness::SpellTracker::LegacyTracker::draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis)
{
	std::string cd = std::to_string(static_cast<int>(std::round(spell.get_cooldown() + 1)));

	float fractal = spell.get_cooldown() / spell.get_max_cooldown();

	float currentWidth = legacySlotDimension.x - (legacySlotDimension.x * fractal);

	Vec2 end = { root.x + currentWidth, root.y + 8 };
	Vec2 textSize = draw_manager->calc_text_size(cd, 14);
	Vec2 middle = { root.x + 12.0f - (textSize.x / 2), root.y + 8.0f };

	draw_manager->screen_rectangle(root, end, is_stasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::Legacy::progressbar, 0.0f, 1.0f, true);
	draw_manager->screen_text(middle, cd, Colors::SpellTracker::Legacy::cooldown_font, 14);
}
#pragma endregion

#pragma region Modern Tracker
void Awareness::SpellTracker::ModernTracker::draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots)
{
	bool isStasis = entity->is_invulnerable();
	Vec2 backgroundBarRoot		= (entity->get_health_bar_screen_position() + minimalHpBarPosOffset);
	Vec2 backgroundBarEnd		= (backgroundBarRoot + minimalHpBarPosSize);
	Vec2 shadowBarRoot			= backgroundBarRoot + minimalShadowbarOffset;
	Vec2 shadowBarEnd			= shadowBarRoot + minimalShadowbarDimension;
	Vec2 sumsBackgroundRoot = entity->get_health_bar_screen_position() + minimalSumsOffset + minimalSumsBackgroundOffset;
	Vec2 sumsBackgroundEnd{};
	sumsBackgroundEnd.x = sumsBackgroundRoot.x + minimalSumsDimensions.x + (-2 * minimalSumsBackgroundOffset.x);
	sumsBackgroundEnd.y = sumsBackgroundRoot.y + (2 * minimalSumsDimensions.y) + (-2 * minimalSumsBackgroundOffset.y);

	draw_manager->screen_rectangle(backgroundBarRoot, backgroundBarEnd, Colors::SpellTracker::Modern::border, 1.0f, 1.0f, true);
	draw_manager->screen_rectangle(sumsBackgroundRoot, sumsBackgroundEnd, Colors::SpellTracker::Modern::border, 1.0f, 1.0f, true);
	draw_manager->screen_rectangle(shadowBarRoot, shadowBarEnd, Colors::SpellTracker::Modern::background, 1.0f, 1.0f, true);

	int j = 0;
	for (int i = 0; i < slots.size(); i++)
	{
		const auto spell_slot = slots[i];
		const auto casted_spell = casted_spells[entity][(int)spell_slot->get_slot_id()];
		void* texture = spell_slot->get_icon();
		
		if (i > 3)
		{
			Vec2 root, end, vDisplacement;
			vDisplacement.y = j * minimalSumsDimensions.y;
			root = entity->get_health_bar_screen_position() + minimalSumsOffset + vDisplacement;
			end = root + minimalSumsDimensions;

			if (!casted_spell.is_ready())
			{
				std::string cd = std::to_string(static_cast<int>(std::round(casted_spell.get_cooldown() + 1)));

				Vec2 textSize = draw_manager->calc_text_size(cd, 14);
				Vec2 middle = { root.x - 13.0f - (textSize.x / 2),
								root.y + 8.0f - (textSize.y / 2) };

				draw_manager->texture(texture, root, minimalSumsDimensions, 2.0f, isStasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::dark_red);
				draw_manager->screen_text(middle, cd, Color(255, 255, 255, 255), 14);
			}
			else
			{
				draw_manager->texture(texture, root, minimalSumsDimensions, 2.0f, isStasis ? Colors::SpellTracker::stasis : Color{255,255,255,255});
			}

			j++;
			continue;
		}

		if (spell_slot->get_level() == 0) continue;

		Vec2 slotRoot =
		{
			minimalSlotStart.x + backgroundBarRoot.x + ((i + 1) * minimalSlotOffset.x) + (i * minimalSlotDimension.x),
			minimalSlotOffset.y + backgroundBarRoot.y
		};

		Vec2 slotEnd = slotRoot + minimalSlotDimension;

		if (!casted_spell.is_ready())
		{
			ModernTracker::draw_progress_bar(casted_spell, slotRoot, isStasis);
		}
		else {
			draw_manager->screen_rectangle(slotRoot, slotEnd, isStasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::Modern::green, 1.0f, 1.0f, true);
		}
	}
}

void Awareness::SpellTracker::ModernTracker::draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis)
{
	byte r, g;
	float fractal = spell.get_cooldown() / spell.get_max_cooldown();

	std::string cd = std::to_string(static_cast<int>(std::round(spell.get_cooldown() + 1)));

	float currentWidth = minimalSlotDimension.x - (minimalSlotDimension.x * fractal);
	Vec2 end = { root.x + currentWidth, root.y + 5 };

	r = 255 - (131 * (1 - fractal));
	g = 27 + (200 * (1 - fractal));
	Color col{ r, g , 4, 255};

	draw_manager->screen_rectangle(root, end, is_stasis ? Colors::SpellTracker::stasis : col, 1.0f, 1.0f, true);
}
#pragma endregion

#pragma region Chimera Tracker
void Awareness::SpellTracker::ChimeraTracker::draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots)
{
	bool isStasis = entity->is_invulnerable();
	Vec2 entityHpBar = entity->get_health_bar_screen_position();

	int j = 0;
	for (int i = 0; i < slots.size(); i++)
	{
		const auto spell_slot = slots[i];
		const auto casted_spell = casted_spells[entity][(int) spell_slot->get_slot_id()];
		void* texture = spell_slot->get_icon();

		Vec2 slotRoot =
		{
			entityHpBar.x + chimeraHpBarOffset.x + (i * chimeraIconSize.x) + (i * chimeraShadowRadius),
			entityHpBar.y + chimeraHpBarOffset.y + 5.0f
		};

		if (i > 3)
		{
			Vec2 root, end, displacement;
			displacement.y = j * (-20);
		
			root = entity->get_health_bar_screen_position() + chimeraSumsOffset + displacement;

			if (!casted_spell.is_ready())
			{
				std::string cd = std::to_string(static_cast<int>(std::round(casted_spell.get_cooldown() + 1)));

				Vec2 textSize = draw_manager->calc_text_size(cd, 14);
				Vec2 middle = { root.x + 35.0f - (textSize.x / 2) - 4.f,
								root.y + 11.0f - (textSize.y / 2) - 2.f };

				draw_manager->texture(texture, root, chimeraSumsDimensions, 14.0f, isStasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::dark_red);
				draw_manager->screen_text(middle, cd, Color(255, 255, 255, 255), 14);
			}
			else
			{
				draw_manager->texture(texture, root, chimeraSumsDimensions, 14.0f, isStasis ? Colors::SpellTracker::stasis : Color{ 255,255,255,255 });
			}

			j++;
			continue;
		}

		draw_manager->texture(texture, (slotRoot - (chimeraIconSize / 2)), chimeraIconSize, 20.0f, isStasis ? Colors::SpellTracker::stasis : Color{ 255,255,255, 255 });

		if (spell_slot->get_level() == 0)
		{
			draw_manager->screen_circle(slotRoot, chimeraIconSize.x / 2, Colors::SpellTracker::LeagueHub::unleveled_background, 1.0f, true);
			draw_manager->screen_arc(slotRoot, chimeraShadowRadius, 0.0f, M_PI * 2.0f * 1.0f, Colors::SpellTracker::LeagueHub::unleveled_border, 2.0f);
			continue;
		}

		if (!casted_spell.is_ready())
		{
			ChimeraTracker::draw_progress_bar(casted_spell, slotRoot, isStasis);
		}
		else {
			ChimeraTracker::draw_level_indicator(slotRoot, spell_slot, isStasis);
		}
	}

}

void Awareness::SpellTracker::ChimeraTracker::draw_level_indicator(const Vec2& root, SpellSlot* spell, bool is_stasis)
{
	draw_manager->screen_arc(root, chimeraShadowRadius, 0.0f, M_PI * 2.0f * 1.0f, is_stasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::pacific_blue, 2.0f);
	if (spell->get_level() < 2)
	{

	}
	else {
		//draw_manager->testPie(root, 13.0f, 15.0f, spell->get_level(), is_stasis ? Colors::SpellTracker::stasis : Colors::SpellTracker::pacific_blue, Colors::SpellTracker::LeagueHub::background);
	}
}

void Awareness::SpellTracker::ChimeraTracker::draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis)
{
	byte r,g,b = 0;
	float fractal = spell.get_cooldown() / (spell.get_cooldown_mod() * spell.get_max_cooldown());
	std::string cd = std::to_string(static_cast<int>(std::round(spell.get_cooldown() + 1)));
	Vec2 textSize = draw_manager->calc_text_size(cd, 12);
	Vec2 middle = { root.x - (textSize.x / 2) + 1.0f , root.y - 6.0f };

	r = 255 - ( 55 * (1 - fractal));
	g =   0 + (236 * (1 - fractal));
	b =  40 + ( 30 * (1 - fractal));
	Color col{ r, g , b, 255 };

	draw_manager->screen_circle(root, chimeraShadowRadius, Colors::SpellTracker::LeagueHub::background, 5.0f);
	draw_manager->screen_circle(root, chimeraIconSize.x / 2, Colors::SpellTracker::drop_shadow, 1.0f, true);
	draw_manager->screen_arc(root, chimeraShadowRadius, -(M_PI / 2), -M_PI * 2.0f * (1 - fractal) - (M_PI / 2), is_stasis ? Colors::SpellTracker::stasis : col, 3.0f);
	draw_manager->screen_text(middle, cd, Colors::SpellTracker::Legacy::cooldown_font, 12);
}
#pragma endregion