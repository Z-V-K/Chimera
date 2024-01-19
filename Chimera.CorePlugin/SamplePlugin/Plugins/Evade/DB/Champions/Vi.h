#pragma once
#include "../EvadeSpellData.h"

// TODO: Vi E cone maybe
class Vi
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Vi, "Vi Q");
		q_data
			->set_spell_hashes({ spell_hash("ViQCast") })
			->set_object_names({ "ViQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(1400.0f)
			->set_radius(60.0f) // 55.0f wiki
			->set_collision_objects({ CollisionObject::Heroes })
			->set_range([](DetectedSpell* spell)
			{
				// TODO; custom charge: spell_hash("ViQ")
				return 1000.f; // max range.
			});
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