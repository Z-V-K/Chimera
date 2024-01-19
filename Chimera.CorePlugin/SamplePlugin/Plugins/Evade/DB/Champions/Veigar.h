#pragma once
#include "../EvadeSpellData.h"

class Veigar
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Veigar, "Veigar Q");
		q_data->set_spell_hashes({ spell_hash("VeigarBalefulStrike") })
			->set_object_names({ "VeigarBalefulStrikeMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1000.f)
			->set_radius(70.f)
			->set_delay(.25f)
			->set_missile_speed(2200.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_is_dangerous(true);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Veigar, "Veigar W");
		w_data->set_spell_hashes({ spell_hash("VeigarDarkMatter") })
			->set_type(EvadeSpellType::Circle)
			->set_range(900.f)
			->set_radius(240.f)
			->set_delay(1.221f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);

		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Veigar, "Veigar E");
		e_data->set_spell_hashes({ spell_hash("VeigarEventHorizon") })
			->set_type(EvadeSpellType::Ring)
			->set_range(725.f)
			->set_radius(350.f)
			->set_ring_radius(50.f)
			->set_delay(.75f)
			->set_duration(3.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
			->set_is_dangerous(true);

		spells.push_back(e_data);
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