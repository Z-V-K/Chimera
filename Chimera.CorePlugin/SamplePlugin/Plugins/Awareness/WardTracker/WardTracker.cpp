#include "WardTracker.h"
#include "../Awareness.h"
#include "../Colors.h"

std::unordered_map<GameObject*, Geometry::Polygon> wardMap;
std::unordered_map<CharacterHash, float> rangeMap;
std::unordered_map<CharacterHash, uint32_t> buffMap;


PVOID enemyWardTexture, enemyPinkWardTexture, ghostPoroIcon, fiddleSticksIcon, defaultIcon;

float progressCircleSize;
Vec2 casterIconSize;
Vec2 offset;
Vec2 minimapMarkerSize;

// JammerDevice			-> Buff: JammerDevice					| 0xE0A02BA3
// YellowTrinket		-> Buff: sharedstealthwardbuff			| 0xA6FE5B28
// SupportItem			-> Buff: sharedstealthwardbuff			| 0xA6FE5B28
// FiddleSticksEffigy	-> Buff: FiddleSticksScarecrowEffigy	| 0x156E7137
// BlueTrinket			-> Buff: relicblueward					| 0xFA1E9DEA
// ZombieWard			-> Buff: relicblueward					| 0xFA1E9DEA
		 
void Awareness::WardTracker::initialize()
{
	buffMap =
	{
		{ CharacterHash::YellowTrinket,			0xA6FE5B28 },
		{ CharacterHash::ControlWard,			0xE0A02BA3 },
		{ CharacterHash::SupportItem,			0xA6FE5B28 },
		{ CharacterHash::BlueTrinket,			0xFA1E9DEA },
	    //{ CharacterHash::GhostPoro,			0x0 },
		{ CharacterHash::ZombieWard,			0xFA1E9DEA },
		{ CharacterHash::FiddleSticksTrinket,	0x156E7137 },
	};	
	
	rangeMap =
	{
		{ CharacterHash::YellowTrinket,			900.0f },
		{ CharacterHash::ControlWard,			900.0f },
		{ CharacterHash::SupportItem,			900.0f },
		{ CharacterHash::BlueTrinket,			500.0f },
		{ CharacterHash::GhostPoro,				450.0f },
		{ CharacterHash::ZombieWard,			900.0f },
		{ CharacterHash::FiddleSticksTrinket,	900.0f },
	};

	enemyWardTexture = renderer->get_texture_from_game("assets/ux/minimap/icons/minimap_ward_green_enemy_new.tex");
	enemyPinkWardTexture = renderer->get_texture_from_game("assets/ux/minimap/icons/minimap_ward_pink_enemy.tex");
	ghostPoroIcon = renderer->get_texture_from_game("assets/perks/styles/domination/ghostporo/ghostporo.dds");
	fiddleSticksIcon = renderer->get_texture_from_game("assets/characters/fiddlesticks/hud/fiddlesticks_circle_0.dds");
	defaultIcon = renderer->get_texture_from_game("assets/ux/summonericons/profileicon29.dds"); // helmetbro

	progressCircleSize =  20.0f;
	casterIconSize = { 35.0f, 35.0f };
	offset = { 0.0f, - 130.0f };
	minimapMarkerSize = { 25.0f, 25.0f };

	Color red{ 230, 0, 0, 125 };
	Color white{ 255, 255, 255, 125 };

	Menu::draw_enemy_wards =				Awareness::Menu::tab_ward_tracker->add_checkbox("draw_enemy_wards", "Draw Enemy Wards", true);
	Menu::ward_glow_colour =				Awareness::Menu::tab_ward_tracker->add_colorpick("ward_glow_colour", "Glow", red);
	Menu::ward_range_indicator_col =		Awareness::Menu::tab_ward_tracker->add_colorpick("meWardRangeIndictorCol", "Indicator Colour", white);
	Menu::ward_range_indicator_thickness =	Awareness::Menu::tab_ward_tracker->add_slider("meWardRangeIndictor", "Indicator Thickness", 5, 3, 10);

	Awareness::Menu::tab_ward_tracker->set_enabled(Menu::draw_enemy_wards);

	callbacks<EventType::OnDraw>::add_callback(on_draw, "WardTracker");
	callbacks<EventType::OnDrawEnvironment>::add_callback(on_draw_environment, "WardTracker");
	callbacks<EventType::OnSlowTick>::add_callback(on_slow_tick, "WardTracker");
	callbacks<EventType::OnDeleteObject>::add_callback(on_delete_object, "WardTracker");
}

void Awareness::WardTracker::on_unload()
{
	for (const auto& obj : wardMap)
	{
		glow->remove_object(obj.first);
	}
}

void Awareness::WardTracker::on_draw_environment()
{
	for (const auto& wardEntry : wardMap)
	{
		wardEntry.second.draw(Colors::WardTracker::wisteria, 2.0f, false);
		draw_timer(wardEntry.first);
		draw_minimap_tracker(wardEntry.first);
		glow_ward(wardEntry.first);
	}
}

void Awareness::WardTracker::on_draw()
{
	for (const auto& wardEntry : wardMap)
	{
		draw_minimap_tracker(wardEntry.first);
	}
}

void Awareness::WardTracker::on_slow_tick()
{
	auto minions_list = entities->get_minions();

	for (const auto& ward : minions_list)
	{
		if (!ward->is_enemy())
			continue;
		
		if (!ward->is_ward())
			continue;

		wardMap.insert({ ward, get_real_ward_range(ward->get_position(), rangeMap[ward->get_character_hash()]) });
	}

	for (const auto& entry : wardMap)
	{
		const auto ward{ entry.first };

		if (!ward || (ward->get_max_mana() > 0 && ward->get_mana() <= 0) || !ward->is_alive() || !ward->is_ward())
		{
			wardMap.erase(ward);
			glow->remove_object(ward);
		}
	}
}

void Awareness::WardTracker::on_delete_object(GameObject* obj)
{
	if (obj && obj->is_ward() && wardMap.contains(obj))
	{
		wardMap.erase(obj);
		glow->remove_object(obj);
	}
}

Geometry::Polygon Awareness::WardTracker::get_real_ward_range(const Vec3& pos, const int range = 1100.0f)
{
	const int sectorCount = 100;
	Geometry::Polygon poly;

	float fractal = (M_PI * 2.f) / sectorCount;	

	for (float theta = 0; theta < (M_PI * 2.f); theta += fractal)
	{
		Vec3 p = pos;

		for (float step = 5.f; step <= range; step += 10.f)
		{
			Vec3 p2{ pos.x + (step * cos(theta)), pos.y, pos.z - (step * sin(theta)) };
			p2.y = nav_mesh->get_height_for_position(p2);;

			const auto posFlag = nav_mesh->get_pos_flags(p2);

			/*auto isFOWGrass = [posFlag, p2]() -> bool
			{
				return (posFlag == CellFlags::UnkGrass || posFlag == CellFlags::Grass || posFlag == CellFlags::PropGrass) && nav_mesh->is_in_fow(p2);
			};*/

			if (/*isFOWGrass() ||*/
				posFlag == CellFlags::Wall || 
				posFlag == CellFlags::Building || 
				posFlag == CellFlags::PropWall ||
				posFlag == CellFlags::UnkWall ||
				step == range)
				break;

			p = p2;
		}

		poly.points.push_back(p);
	}
	
	return poly;
}

void Awareness::WardTracker::draw_timer(GameObject* obj)
{
	if (!obj || !obj->is_visible_on_screen())
		return;

	PVOID casterIcon{ defaultIcon };

	const auto casterBuffHashIt = buffMap.find(obj->get_character_hash());

	if (casterBuffHashIt == buffMap.end())
		return;

	const auto casterBuffHash = casterBuffHashIt->second;

	for (const auto& buff : obj->get_buffs())
	{
		if (buff->get_hash() == casterBuffHash)
		{
			if (const auto caster = buff->get_caster())
				casterIcon = caster->get_circle_icon();
		}
	}
	
	std::string cd = std::to_string((int)(obj->get_mana() + 0.5f));
	std::string hp = std::to_string((int)(obj->get_health()));
	std::string text = cd + " | " + hp;
	Vec2 root{ renderer->world_to_screen(obj->get_position()) + offset };
	Vec2 root2{};
	root2.x = root.x - (progressCircleSize) + 0.5f;
	root2.y = root.y + progressCircleSize   + 3.0f;
	Vec2 end{};
	end.x = root2.x + 40.0f;
	end.y = root2.y + 15.0f;
	Vec2 textSize = draw_manager->calc_text_size(text, 12);
	Vec2 middle = { root2.x - (textSize.x / 2) + 20.5f , root2.y + 1.5f };
	Vec2 middle2 = { root2.x - (textSize.x / 2) + 26.5f , root2.y + 1.5f };

	Color col{ 0,0,0,0 };
	float fractal{0.0f};

	switch (obj->get_character_hash())
	{
		case CharacterHash::YellowTrinket:
		case CharacterHash::SupportItem:
			col = Colors::WardTracker::golden_yellow;
			fractal = obj->get_mana() / obj->get_max_mana();
			break;
		case CharacterHash::ControlWard:
			col = Colors::WardTracker::cherry;
			break;
		case CharacterHash::ZombieWard:
			text = cd;
			middle = middle2;
			fractal = obj->get_mana() / obj->get_max_mana();
		case CharacterHash::GhostPoro:
			text = cd;
			middle = middle2;
			col = Colors::WardTracker::rose;
			casterIcon = ghostPoroIcon;
			break;
		case CharacterHash::FiddleSticksTrinket:
			text = cd;
			middle = middle2;
			col = Colors::WardTracker::salmon;
			casterIcon = fiddleSticksIcon;
			break;
		case CharacterHash::BlueTrinket:
			text = cd;
			middle = middle2;
			col = Colors::WardTracker::ocean_blue;
			break;
		default:
			break;
	}

	draw_manager->texture(casterIcon, root - (casterIconSize / 2), casterIconSize, 20.0f, Color{ 255,255,255, 255 });
	draw_manager->screen_circle(root, progressCircleSize, Colors::WardTracker::background, 4.0f);
	draw_manager->screen_arc(root, progressCircleSize, -(M_PI / 2), -M_PI * 2.0f * (fractal) - (M_PI / 2), col, 3.0f);

	draw_manager->screen_rectangle(root2, end, Colors::WardTracker::background_timer, 10.0f, 1.0f, true);
	draw_manager->screen_text(middle, text, Color{ 255,255,255,255 }, 12);
}

void Awareness::WardTracker::draw_minimap_tracker(GameObject* obj)
{
	if (!obj)
		return;

	const auto posOnMinimap = renderer->world_to_minimap(obj->get_position());

	PVOID marker{ enemyWardTexture };

	if (obj->get_character_hash() == CharacterHash::ControlWard)
		marker = enemyPinkWardTexture;

	draw_manager->texture(marker, posOnMinimap - (minimapMarkerSize / 2), minimapMarkerSize, 0.0f, Color{ 255, 255, 255, 255 });
}

void Awareness::WardTracker::glow_ward(GameObject* obj)
{
	if (glow->is_glowing(obj))
		return;

	Color glow_col;

	switch (obj->get_character_hash())
	{
	case CharacterHash::YellowTrinket:
	case CharacterHash::SupportItem:
		glow_col = Colors::WardTracker::golden_yellow;
		break;
	case CharacterHash::ControlWard:
		glow_col = Colors::WardTracker::cherry;
		break;
	case CharacterHash::FiddleSticksTrinket:
	case CharacterHash::ZombieWard:
	case CharacterHash::GhostPoro:
		glow_col = Colors::WardTracker::salmon;
		break;
	case CharacterHash::BlueTrinket:
		glow_col = Colors::WardTracker::ocean_blue;
		break;
	default:
		break;
	}

	glow->register_object(obj, glow_col, 2, 5);
}