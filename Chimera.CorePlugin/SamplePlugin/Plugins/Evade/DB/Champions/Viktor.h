#pragma once
#include "../EvadeSpellData.h"

// TODO: Viktor E
class Viktor
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Viktor, "Viktor W");
		w_data
			->set_spell_hashes({ spell_hash("ViktorGravitonField") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(4.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(290.0f)
			->set_range(800.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Viktor, "Viktor E");
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Viktor, "Viktor R");
		r_data
			//->set_spell_hashes({ spell_hash("ViktorDeathRay") })
			->set_object_names({ "ViktorDeathRayMissile", "ViktorEAugMissile", "ViktorDeathRayMissile2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			//->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_missile_speed(1500.0f)
			->set_radius(50.0f) // 45.0f wiki
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(550.0f);
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