#pragma once
#include "../EvadeSpellData.h"

class Anivia
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Anivia, "Anivia Q");
		q_data->set_spell_hashes({ spell_hash("FlashFrostSpell") })
			->set_object_names({ "FlashFrostSpell" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1100.f + 225.f / 2)
			->set_radius(110.f + 225.f / 2)
			->set_delay(.25f)
			->set_missile_speed(950.f)
			->set_is_range_fixed(true)
			->set_add_bounding(false)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::VeryHigh);
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