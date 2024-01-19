#pragma once
#include "../EvadeSpellData.h"

class Fizz
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Fizz, "Fizz E");
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Fizz, "Fizz R");
		r_data->set_spell_hashes({ spell_hash("FizzR") })
			->set_object_names({ "FizzRMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_missile_speed(1300.f)
			->set_radius(120.f)
			->set_is_hard_cc(true)
			->set_has_end_explosion(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes })
			->set_range(1250.f);

		//r_data->end_explosion = new EvadeSpellData(CharacterHash::Fizz, "Fizz R end explosion");
		//r_data->end_explosion
		//	->set_object_names(r_data->object_names)
		//	->set_is_dangerous(r_data->is_dangerous)
		//	->set_range(r_data->range)
		//	->set_is_range_limited(true)
		//	->set_missile_speed(r_data->missile_speed)
		//	->set_type(EvadeSpellType::Circle)
		//	->set_radius(450.f)
		//	->set_danger_level(DangerLevel::VeryHigh)
		//	->set_is_dangerous(true)
		//	->set_is_hard_cc(true);
		//spells.push_back(r_data);

		// TODO; R ground
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