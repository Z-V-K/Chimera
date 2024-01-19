#pragma once
#include "../EvadeSpellData.h"

class Zoe
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Zoe, "Zoe Q");
		q_data
			//->set_spell_hashes({ spell_hash("ZoeQ") })
			->set_object_names({ "ZoeQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(false)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.f)
			->set_radius(50.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1150.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Zoe, "Zoe Q Recast");
		q_data
			->set_spell_hashes({ spell_hash("ZoeQ2") })
			->set_object_names({ "ZoeQMis2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(false)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1850.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1300.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Zoe, "Zoe E Ground");
		e_data
			//->set_spell_hashes({ spell_hash("ZoeEBubble") })
			->set_object_names({ "ZoeEc" })
			->set_type(EvadeSpellType::Circle)
			->set_duration(6.0f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(1850.0f)
			->set_radius(250.0f)
			->set_range(850.0f);
		spells.push_back(e_data);

		e_data = new EvadeSpellData(CharacterHash::Zoe, "Zoe E Missile");
		e_data
			->set_spell_hashes({ spell_hash("ZoeE") })
			->set_object_names({ "ZoeEMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(false)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.3f)
			->set_missile_speed(1850.0f)
			->set_radius(45.0f)
			->set_range(850.f)
			->set_collision_objects({ CollisionObject::Minions, CollisionObject::Heroes, CollisionObject::YasuoWall });
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