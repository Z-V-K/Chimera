#pragma once
#include "../EvadeSpellData.h"

class Ornn
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Ornn, "Ornn Q");
		q_data
			->set_spell_hashes({ spell_hash("OrnnQ") })
			->set_object_names({ "OrnnQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.3f)
			->set_missile_speed(1800.0f)
			->set_radius(65.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(750.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Ornn, "Ornn E");
		e_data
			->set_spell_hashes({ spell_hash("OrnnE") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.35f)
			->set_missile_speed(1600.0f)
			->set_radius(100.0f)
			->set_collision_objects({ CollisionObject::GameWall })
			->set_range(850.0f)
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Ornn, "Ornn R");
		r_data
			->set_object_names({ "OrnnRWave" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.5f)
			->set_missile_speed(1250.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_radius(250.0f)
			->set_range(2550.0f);
		spells.push_back(r_data);

		r_data = new EvadeSpellData(CharacterHash::Ornn, "Ornn R Recast");
		r_data
			//->spellNames({ "OrnnRCharge" })
			->set_object_names({ "OrnnRWave2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(1650.0f)
			->set_radius(200.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(3500.0f);
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