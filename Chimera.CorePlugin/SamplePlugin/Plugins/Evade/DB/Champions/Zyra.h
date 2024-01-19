#pragma once
#include "../EvadeSpellData.h"

class Zyra
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Zyra, "Zyra Q");
		q_data
			->set_spell_hashes({ spell_hash("ZyraQ") })
			->set_type(EvadeSpellType::Line)
			->set_range(800.f)
			->set_radius(90.f)
			->set_delay(0.875f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_perpendicular(true)
			->set_perpendicular_length(450.f)
			->set_add_bounding(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Zyra, "Zyra E");
		e_data
			->set_spell_hashes({ spell_hash("ZyraE") })
			->set_object_names( { "ZyraE "})
			->set_type(EvadeSpellType::MissileLine)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1150.f)
			->set_radius(70.f)
			->set_delay(0.25f)
			->set_missile_speed(1150.0f)
			->set_danger_level(DangerLevel::High)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(true);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Zyra, "Zyra R");
		r_data
			->set_spell_hashes({ spell_hash("ZyraR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(2.0f)
			->set_radius(500.0f)
			->set_range(700.0f);
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