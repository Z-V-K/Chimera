#pragma once
#include "../EvadeSpellData.h"

class Akali
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Akali, "Akali Q");

		q_data->set_spell_hashes({ spell_hash("AkaliQ") })
			->set_type(EvadeSpellType::Cone)
			->set_range(500.f)
			->set_radius(45.f)
			->set_danger_level(DangerLevel::Medium)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_range_fixed(true)
			->set_is_dangerous(true);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Akali, "Akali E");

		e_data->set_spell_hashes({ spell_hash("AkaliE") })
			->set_object_names({ "AkaliEMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(825.f)
			->set_radius(60.f)
			->set_delay(.5f)
			->set_missile_speed(1800.f)
			->set_offset_start(-100.f)
			->set_add_bounding(true)
			->set_skip_distance_check(true)
			->set_is_range_fixed(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_danger_level(DangerLevel::High)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Minions, CollisionObject::Heroes })
			->set_is_dangerous(true);

		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Akali, "Akali R2");

		r_data->set_spell_hashes({ spell_hash("AkaliRb") })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(675.f)
			->set_radius(55.f)
			->set_delay(0.f)
			->set_missile_speed(300.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_dangerous(true);

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