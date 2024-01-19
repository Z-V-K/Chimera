#pragma once
#include "../EvadeSpellData.h"

class Gnar
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar Q");
		q_data->set_spell_hashes({ spell_hash("GnarQ") })
			->set_object_names({ "GnarQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Low)
			->set_is_dangerous(false)
			->set_missile_speed(2500.f)
			->set_radius(55.f)
			->set_range(1125.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall });
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar Q return");
		q_data->set_spell_hashes({ spell_hash("GnarQMissileReturn") })
			->set_object_names({ "GnarQMissileReturn" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Low)
			->set_missile_speed(2600.f)
			->set_radius(75.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1125.f);

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar Q big");
		q_data->set_spell_hashes({ spell_hash("GnarBigQ") })
			->set_object_names({ "GnarBigQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.5f)
			->set_missile_speed(2100.f)
			->set_radius(90.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(1150.f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar W");
		w_data->set_spell_hashes({ spell_hash("GnarBigW") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
			->set_delay(.6f)
			->set_radius(120.f)
			->set_range(600.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar E");
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Gnar, "Gnar R");
		r_data->set_spell_hashes({ spell_hash("GnarR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_radius(475.f)
			->set_is_hard_cc(true)
			->set_range(475.f);
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