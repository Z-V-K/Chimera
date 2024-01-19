#pragma once
#pragma once
#include "../EvadeSpellData.h"

class Aphelios
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Aphelios, "Aphelios Q Calibrum");
		q_data->set_spell_hashes({ spell_hash("ApheliosCalibrumQ") })
			->set_object_names({ "ApheliosCalibrumQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1450.f)
			->set_radius(60.f)
			->set_delay(.4f)
			->set_missile_speed(1850.f)
			->set_danger_level(DangerLevel::Medium)
			->set_collision_objects({ CollisionObject::Minions, CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_is_dangerous(false);

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Aphelios, "Aphelios Q Infernum");
		q_data->set_spell_hashes({ spell_hash("ApheliosInfernumQ") })
			->set_object_names({ "ApheliosInfernumQMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(650.f)
			->set_radius(45.f)
			->set_delay(.4f)
			->set_missile_speed(1850.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(false);

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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Aphelios, "Aphelios R");
		r_data->set_spell_hashes({ spell_hash("ApheliosR") })
			->set_object_names({ "ApheliosRMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1300.f)
			->set_radius(110.f)
			->set_missile_speed(1850.f)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_collision_objects({ CollisionObject::YasuoWall });

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