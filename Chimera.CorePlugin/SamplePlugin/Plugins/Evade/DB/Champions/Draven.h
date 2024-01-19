#pragma once
#include "../EvadeSpellData.h"

class Draven
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Draven, "Draven E");
		e_data->set_spell_hashes({ spell_hash("DravenDoubleShot") })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1100.f)
			->set_radius(130.f)
			->set_missile_speed(1400.f)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_dangerous(true);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Draven, "Draven R");
		r_data->set_spell_hashes({ spell_hash("DravenRCast") })
			->set_object_names({ "DravenR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(20000.f)
			->set_radius(160.f)
			->set_delay(.5f)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_add_bounding(true)
			->set_offset_start(50.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_dangerous(true);

		// TODO; R2

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