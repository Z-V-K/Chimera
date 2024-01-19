#pragma once
#include "../EvadeSpellData.h"

class DrMundo
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::DrMundo, "DrMundo Q");
		q_data->set_spell_hashes({ spell_hash("DrMundoQ") })
			->set_object_names({ "DrMundoQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true)
			->set_missile_speed(2000.f)
			->set_radius(60.f)
			->set_range(1050.f)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes, CollisionObject::Minions });
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