#pragma once
#include "../EvadeSpellData.h"

class Lucian
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Lucian, "Lucian Q");
		q_data->set_spell_hashes({ spell_hash("LucianQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(FLT_MAX)
			->set_radius(60.0f)
			->set_range(1000.0f)
			->set_delay([] (DetectedSpell* spell)
			{
				return spell->source ? .4f - .15f / 17.f * (spell->source->get_level() - 1) : .4f;
			});
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Lucian, "Lucian W");
		w_data->set_spell_hashes({ spell_hash("LucianW") })
			->set_object_names({ "LucianWMissile" })
			->set_danger_level(DangerLevel::Low)
			->set_range(900.0f)
			->set_delay(0.25f)
			->set_radius(55.0f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(false)
			->set_missile_speed(1600.0f)
			->set_has_end_explosion(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_type(EvadeSpellType::MissileLine);

		w_data->end_explosion = [](DetectedSpell* spell)
		{
			const auto end_pos = spell->get_end_pos();
			const auto direction = spell->direction;
			const auto perp_direction = direction.perpendicular();
			const auto height = local_player->get_position().y;
			static const float star_width = 500.f;

			Geometry::Rectangle r1{ end_pos.extend(end_pos + direction, -star_width).to_3d(height), end_pos.extend(end_pos + direction, star_width).to_3d(height), 60.f };
			Geometry::Rectangle r2{ end_pos.extend(end_pos + perp_direction, -star_width).to_3d(height), end_pos.extend(end_pos + perp_direction, star_width).to_3d(height), 60.f };

			std::vector<Geometry::Polygon> polygons{ r1.to_polygon(), r2.to_polygon() };
			const auto clipped = Geometry::clip_polygons(polygons);
			const auto clipped_polys = Geometry::to_polygons(clipped);

			if (clipped_polys.empty())
				return r1.to_polygon();

			return clipped_polys[0];
		};
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Lucian, "Lucian R");
		r_data/*->set_spell_hashes({ spell_hash("LucianR") })*/
			->set_object_names({ "LucianRMissile", "LucianRMissileOffhand" })
			->set_danger_level(DangerLevel::Medium)
			->set_range(1200.0f)
			->set_delay(0.0f)
			->set_radius(110.0f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(false)
			->set_missile_speed(1600.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_type(EvadeSpellType::MissileLine);
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