#pragma once
#include "../EvadeSpellData.h"

class Kalista
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Kalista, "Kalista Q");
		q_data->set_spell_hashes({ spell_hash("KalistaMysticShot") })
			->set_object_names({ "KalistaMysticShotMisTrue" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(2400.0f)
			->set_radius(40.0f)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_range(1200.0f);
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
		//EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Kalista, "Kalista R");
		//spells.push_back(r_data);
		// TODO;
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