#pragma once
#include "../EvadeSpellData.h"

class Illaoi
{
private:
	// TODO; passives slam
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Illaoi, "Illaoi Q");
		q_data->set_spell_hashes({ spell_hash("IllaoiQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(.75f)
			->set_radius(100.f)
			->set_range(802.75f + 52.75f)
			->set_offset_start(-52.75f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Illaoi, "Illaoi E");
		e_data->set_spell_hashes({ spell_hash("IllaoiE") })
			->set_object_names({ "IllaoiEMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(1900.f)
			->set_radius(50.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(950.f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Illaoi, "Illaoi R");
		r_data->set_spell_hashes({ spell_hash("IllaoiR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.5f)
			->set_radius(500.f)
			->set_range(500.f);
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