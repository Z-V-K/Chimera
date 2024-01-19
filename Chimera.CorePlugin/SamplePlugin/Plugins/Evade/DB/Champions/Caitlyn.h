#pragma once
#include "../EvadeSpellData.h"

class Caitlyn
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Caitlyn, "Caitlyn Q");
		q_data->set_spell_hashes({ spell_hash("CaitlynQ") })
			->set_object_names({ "CaitlynQ", "CaitlynQ1" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1300.f)
			->set_radius(90.f)
			->set_delay(.625f)
			->set_missile_speed(2200.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_collision_objects({ CollisionObject::YasuoWall });
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Caitlyn, "Caitlyn W");
		w_data->set_object_names({ "Cupcake Trap" })
			->set_type(EvadeSpellType::Circle)
			->set_radius(15.f)
			->set_duration(15.f)
			->set_add_bounding(true)
			->set_is_trap(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Caitlyn, "Caitlyn E");
		e_data->set_spell_hashes({ spell_hash("CaitlynE") })
			->set_object_names({ "CaitlynEMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(800.f)
			->set_radius(70.f)
			->set_delay(.15f)
			->set_missile_speed(1600.f)
			->set_danger_level(DangerLevel::High)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_is_dangerous(true);
		spells.push_back(e_data);
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