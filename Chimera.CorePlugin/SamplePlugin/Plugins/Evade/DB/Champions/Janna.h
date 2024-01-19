#pragma once
#include "../EvadeSpellData.h"

class Janna
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Janna, "Janna Q");
		q_data->set_spell_hashes({ spell_hash("HowlingGale") })
			->set_object_names({ "HowlingGaleSpell" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_delay(3.f)
			->set_missile_speed(880.f)
			->set_radius(120.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1100.f);
		spells.push_back(q_data);

		// TODO; fix
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
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