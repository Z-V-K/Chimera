#pragma once
#include "../EvadeSpellData.h"

class Corki
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Corki, "Corki Q");
		q_data->set_spell_hashes({ spell_hash("PhosphorusBomb") })
			->set_object_names({ "PhosphorusBombMissile", "PhosphorusBombMissileMin" })
			->set_type(EvadeSpellType::Circle)
			->set_range(825.f)
			->set_radius(275.f)
			->set_missile_speed(1000.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Corki, "Corki W");
		w_data->set_spell_hashes({ spell_hash("CarpetBombMega") })
			->set_type(EvadeSpellType::Line)
			->set_range(1800.f)
			->set_radius(100.f)
			->set_delay(0.f)
			->set_missile_speed(1500.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_range_limited(true)
			->set_offset_start(-150.f)
			->set_duration(5.f)
			->set_is_range_fixed(false)
			->set_add_bounding(true)
			->set_is_dangerous(true);

		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Corki, "Corki R");
		r_data->set_spell_hashes({ spell_hash("MissileBarrageMissile") })
			->set_object_names({ "MissileBarrageMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1300.f)
			->set_radius(40.f)
			->set_delay(.175f)
			->set_missile_speed(2000.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes, CollisionObject::Minions })
			->set_is_dangerous(false);
		spells.push_back(r_data);

		r_data = new EvadeSpellData(CharacterHash::Corki, "Corki R2");
		r_data->set_spell_hashes({ spell_hash("MissileBarrageMissile2") })
			->set_object_names({ "MissileBarrageMissile2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1500.f)
			->set_radius(40.f)
			->set_delay(.175f)
			->set_missile_speed(2000.f)
			->set_danger_level(DangerLevel::High)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes, CollisionObject::Minions });

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