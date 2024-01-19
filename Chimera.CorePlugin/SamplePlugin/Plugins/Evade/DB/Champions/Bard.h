#pragma once
#include "../EvadeSpellData.h"

class Bard
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Bard, "Bard Q");
		q_data->set_spell_hashes({ spell_hash("BardQ") })
			->set_object_names({ "BardQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(880.f)
			->set_radius(35.f)
			->set_missile_speed(1500.f)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_collision_objects({ CollisionObject::YasuoWall });
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Bard, "Bard Q2");
		q_data
			->set_object_names({ "BardQMissile2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(550.f)
			->set_radius(30.f)
			->set_missile_speed(1500.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_is_range_fixed(true);

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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Bard, "Bard R");
		r_data->set_spell_hashes({ spell_hash("BardR") })
			->set_object_names({ "BardRMissileRange2" })
			->set_type(EvadeSpellType::Circle)
			->set_range(3400.f)
			->set_radius(350.f)
			->set_delay(.5f)
			->set_missile_speed(2100.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_dangerous(true)
			->set_is_hard_cc(true);
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