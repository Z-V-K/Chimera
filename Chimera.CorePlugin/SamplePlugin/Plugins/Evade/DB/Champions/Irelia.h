#pragma once
#include "../EvadeSpellData.h"

class Irelia
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Irelia, "Irelia W");
		w_data->set_spell_hashes({ spell_hash("IreliaW2") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Low)
			->set_is_dangerous(false)
			->set_missile_speed(15500.f)
			->set_radius(120.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(775.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Irelia, "Irelia E");
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Irelia, "Irelia R");
		r_data->set_spell_hashes({ spell_hash("ireliaR") })
			->set_object_names({ "IreliaR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.4f)
			->set_missile_speed(2000.f)
			->set_radius(160.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(1000.f);
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