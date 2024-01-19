#pragma once
#include "../EvadeSpellData.h"

// TODO: W particle
class Rakan
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Rakan, "Rakan Q");
		q_data
			->set_spell_hashes({ spell_hash("RakanQ") })
			->set_object_names({ "RakanQMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(1850.0f)
			->set_radius(65.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(900.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Rakan, "Rakan W");
		w_data
			->set_spell_hashes({ spell_hash("RakanW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			//->isRangeFixed(true)
			->set_is_dash(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(1700.0f)
			->set_radius(275.0f)
			->set_range(650.0f)
			->set_duration(.35f)
			->set_delay([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
		spells.push_back(w_data);
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