#pragma once
#include "../EvadeSpellData.h"

// TODO: Yorick W
class Yorick
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Yorick, "Yorick E");
		e_data
			->set_spell_hashes({ spell_hash("YorickE") })
			->set_type(EvadeSpellType::CustomPolygon)
			->set_add_bounding(true)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(1800.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(700.0f)
			->set_delay([](DetectedSpell* spell)
			{
				return .33f + spell->get_range() / spell->spell_data->missile_speed(spell);
			});

		e_data->custom_polygon = [](DetectedSpell* spell)
		{
			const auto height = local_player->get_position().y;
			const auto start_pos = (spell->cached_end_pos + spell->direction * (- 120.f)).to_3d(height);
			const auto end_pos = (spell->cached_end_pos + spell->direction * 420.f).to_3d(height);

			return Geometry::Rectangle{ start_pos, end_pos, 150.f }.to_polygon();
		};
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
	}
public:
	static void load(std::vector<EvadeSpellData*>& spells)
	{
		load_q_data(spells);
		load_w_data(spells);
		load_e_data(spells);
		load_r_data(spells);
	}
};