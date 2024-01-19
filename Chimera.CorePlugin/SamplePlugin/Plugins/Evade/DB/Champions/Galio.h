#pragma once
#include "../EvadeSpellData.h"

class Galio
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Galio, "Galio Q");
		q_data->set_spell_hashes({ spell_hash("GalioQ") })
			->set_object_names({ "GalioQMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true)
			->set_is_range_limited(true)
			->set_missile_speed(1400.f)
			->set_duration(2.f)
			->set_radius(200.f)
			->set_range(825.f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Galio, "Galio W");
		//spells.push_back(w_data);
		// TODO;
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Galio, "Galio E");
		e_data->set_spell_hashes({ spell_hash("GalioE") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.4f)
			->set_missile_speed(2300.f)
			->set_radius(80.f)
			->set_range(800.f)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_offset_start(-300.f)
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Galio, "Galio R");
		r_data->set_spell_hashes({ spell_hash("GalioR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_delay(2.75f)
			->set_radius(650.f)
			->set_range(5500.f);
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