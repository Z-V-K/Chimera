#pragma once
#include "../EvadeSpellData.h"

class Fiora
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Fiora, "Fiora Q");
		q_data->set_spell_hashes({ spell_hash("FioraQ") })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.f)
			->set_missile_speed(1100.f)
			->set_radius(65.f)
			->set_range(420.f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Fiora, "Fiora W");
		w_data->set_spell_hashes({ spell_hash("FioraW") })
			->set_object_names({ "FioraWMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(.5f)
			->set_missile_speed(3200.f)
			->set_radius(70.f)
			->set_range(770.f)
			->set_offset_start(-50.f)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes });

		spells.push_back(w_data);


		// TODO; W Stun
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