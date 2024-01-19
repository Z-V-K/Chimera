#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Aatrox
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Aatrox, "Aatrox Q1");
		q_data->set_spell_hashes({ spell_hash("AatroxQ") })
			->set_range(700.f)
			->set_radius(90.f)
			->set_delay(.6f)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::High)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_is_start_pos_from_unit(true);

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Aatrox, "Aatrox Q2");
		q_data->set_spell_hashes({ spell_hash("AatroxQ2") })
			->set_type(EvadeSpellType::CustomPolygon)
			->set_range(520.f)
			->set_radius(260.f)
			->set_delay(.6f)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_is_start_pos_from_unit(true);

		q_data->custom_polygon = [](DetectedSpell* data)
		{
			const auto height = local_player->get_position().y;
			const auto start_pos = data->get_start_pos().to_3d(height);
			const auto end_pos = data->get_end_pos().to_3d(height);

			Geometry::Polygon p1 = Geometry::Rectangle{ start_pos, end_pos, 200.f }.to_polygon();
			Geometry::Polygon p2 = Geometry::Rectangle{ start_pos, end_pos, 350.f }.to_polygon();

			return Geometry::Polygon{ { p1.points[0], p1.points[1], p2.points[2], p2.points[3] } };
		};
		

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Aatrox, "Aatrox Q3");
		q_data->set_spell_hashes({ spell_hash("AatroxQ3") })
			->set_type(EvadeSpellType::Circle)
			->set_radius(300.f)
			->set_delay(.6f)
			->set_is_range_fixed(true)
			->set_offset_start(200.f)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_is_start_pos_from_unit(true);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Aatrox, "Aatrox W");

		w_data->set_spell_hashes({ spell_hash("AatroxW") })
			->set_object_names({ "AatroxW" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(825.f)
			->set_radius(80.f)
			->set_missile_speed(1800.f)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_danger_level(DangerLevel::High)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Minions, CollisionObject::Heroes })
			->set_is_dangerous(true);

		spells.push_back(w_data);
	}


	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		
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
