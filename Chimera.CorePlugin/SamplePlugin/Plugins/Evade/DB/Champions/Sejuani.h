#pragma once
#include "../EvadeSpellData.h"

// TODO: Q might need to be updated
class Sejuani
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Sejuani, "Sejuani Q");
		q_data
			->set_spell_hashes({ spell_hash("SejuaniQ") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_limited(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(1000.0f)
			->set_radius(75.0f)
			->set_range(650.0f)
			->set_extra_range(200.f)
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell) - .2f;
			});
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Sejuani, "Sejuani W");
		w_data
			->set_spell_hashes({ spell_hash("SejuaniW") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_start_pos_from_unit(true)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(1.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(90.0f) // wiki 75.0f
			->set_range(625.0f); // wiki 600.0f
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Sejuani, "Sejuani R");
		r_data
			->set_spell_hashes({ spell_hash("SejuaniR") })
			->set_object_names({ "SejuaniRMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(120.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(1300.0f);
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