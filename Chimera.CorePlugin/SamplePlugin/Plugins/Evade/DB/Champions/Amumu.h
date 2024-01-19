#pragma once
#include "../EvadeSpellData.h"

class Amumu
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Amumu, "Amumu Q");

		q_data->set_spell_hashes({ spell_hash("BandageToss") })
			->set_object_names({ "SadMummyBandageToss" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1100.f)
			->set_radius(80.f)
			->set_missile_speed(2000.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Minions, CollisionObject::Heroes })
			->set_is_dangerous(true)
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Amumu, "Amumu R");

		r_data->set_spell_hashes({ spell_hash("CurseoftheSadMummy") })
			->set_type(EvadeSpellType::Circle)
			->set_radius(550.f)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Extreme);

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