#pragma once
#include "../EvadeSpellData.h"

class Orianna
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Orianna, "Orianna Q");
		q_data
			->set_spell_hashes({ spell_hash("OrianaIzunaCommand") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(false)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_missile_speed(1400.0f)
			->set_radius(80.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(825.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Orianna, "Orianna Q Circle");
		q_data
			->set_spell_hashes({ spell_hash("OriannaQCircleSpecial") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(175.0f)
			->set_range(825.0f);
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Orianna, "Orianna R");
		r_data
			->set_spell_hashes({ spell_hash("OrianaDetonateCommand") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(410.0f)
			->set_range(410.0f);
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