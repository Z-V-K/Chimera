#pragma once
#include "../EvadeSpellData.h"

class Azir
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Azir, "Azir Q");
		//spells.push_back(q_data);
		// TODO;
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Azir, "Azir E");
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Azir, "Azir R");
		r_data->set_spell_hashes({ spell_hash("AzirR") })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(750.f)
			->set_radius(285.f)
			->set_missile_speed(1400.f)
			->set_offset_start(-325.f)
			->set_is_range_fixed(true)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_danger_level(DangerLevel::High)
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