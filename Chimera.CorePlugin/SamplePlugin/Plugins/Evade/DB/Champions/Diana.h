#pragma once
#include "../EvadeSpellData.h"

class Diana
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Diana, "Diana Q");
		q_data->set_spell_hashes({ spell_hash("DianaQ") })
			->set_range(800.f)
			->set_is_range_limited(true)
			->set_missile_speed(1900.f)
			->set_type(EvadeSpellType::CustomPolygon)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true)
			->set_has_end_explosion(true)
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			})
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes, CollisionObject::Minions });

		q_data->custom_polygon = [](DetectedSpell* spell)
		{
			const auto height = local_player->get_position().y;
			const auto start_pos = spell->get_start_pos();
			const auto end_pos = spell->get_end_pos();
			const auto perpendicular_dir = spell->direction.perpendicular();

			Geometry::Rectangle rect{ start_pos.extend(start_pos + perpendicular_dir, -200.f).to_3d(height), end_pos.extend(end_pos + perpendicular_dir, -200.f).to_3d(height), 200.f };
			return rect.to_polygon();
		};

		/*q_data->end_explosion = new EvadeSpellData(CharacterHash::Diana, "Diana Q end explosion");
		q_data->end_explosion
			->set_duration(q_data->duration)
			->set_is_dangerous(q_data->is_dangerous)
			->set_range(q_data->range)
			->set_is_range_limited(true)
			->set_missile_speed(q_data->missile_speed)
			->set_type(EvadeSpellType::Circle)
			->set_radius(150.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);*/

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Diana, "Diana R");
		r_data->set_spell_hashes({ spell_hash("DianaR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_range(475.f)
			->set_radius(475.f)
			->set_delay(.25f)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_is_dangerous(true);
		spells.push_back(r_data);
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