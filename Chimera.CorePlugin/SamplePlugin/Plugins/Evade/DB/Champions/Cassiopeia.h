#pragma once
#include "../EvadeSpellData.h"

class Cassiopeia
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Cassiopeia, "Cassiopeia Q");
		q_data->set_spell_hashes({ spell_hash("CassiopeiaQ") })
			->set_type(EvadeSpellType::Circle)
			->set_range(850.f)
			->set_radius(180.f)
			->set_delay(.7f)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Cassiopeia, "Cassiopeia W");
		//spells.push_back(w_data);
		// TODO;
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Cassiopeia, "Cassiopeia R");
		r_data->set_spell_hashes({ spell_hash("CassiopeiaR") })
			->set_type(EvadeSpellType::Cone)
			->set_range(810.f)
			->set_radius(85.f)
			->set_delay(.5f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
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