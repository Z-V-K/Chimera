#pragma once
#include "../EvadeSpellData.h"

class Blitzcrank
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Blitzcrank, "Blitzcrank Q");

		q_data->set_spell_hashes({ spell_hash("RocketGrab") })
			->set_object_names({ "RocketGrabMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1115.f)
			->set_radius(70.f)
			->set_missile_speed(1800.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall });

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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Blitzcrank, "Blitzcrank R");
		r_data->set_spell_hashes({ spell_hash("StaticField") })
			->set_type(EvadeSpellType::Circle)
			->set_radius(600.f)
			->set_danger_level(DangerLevel::Low)
			->set_is_range_fixed(true);

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