#pragma once
#include "../EvadeSpellData.h"

class Jhin
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Jhin, "Jhin W");
		w_data->set_spell_hashes({ spell_hash("JhinW") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High) //TODO; custom danger based on jhin root buff
			->set_delay(.75f)
			->set_offset_start(-20.f)
			->set_radius(35.f)
			->set_range(2520.f + 20.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Jhin, "Jhin E");
		e_data->set_spell_hashes({ spell_hash("JhinE") })
			->set_object_names({ "Noxious Trap" })
			->set_type(EvadeSpellType::Circle)
			->set_add_bounding(false)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(1.f)
			->set_radius(160.f)
			->set_range(750.f)
			->set_range(750.f)
			->set_is_trap(true);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Jhin, "Jhin R");
		r_data->set_spell_hashes({ spell_hash("JhinRShot") })
			->set_object_names({ "JhinRShotMis", "JhinRShotMis4" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High) // TODO custom for 4th shot
			->set_missile_speed(5000.f)
			->set_radius(80.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(3500.f);
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