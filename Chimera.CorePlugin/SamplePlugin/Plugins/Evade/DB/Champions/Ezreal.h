#pragma once
#include "../EvadeSpellData.h"

class Ezreal
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Ezreal, "Ezreal Q");
		q_data->set_spell_hashes({ spell_hash("EzrealQ") })
			->set_object_names({ "EzrealQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1200.f)
			->set_radius(60.f)
			->set_missile_speed(2000.f)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes, CollisionObject::Minions });
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Ezreal, "Ezreal W");
		w_data->set_spell_hashes({ spell_hash("EzrealW") })
			->set_object_names({ "EzrealW" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1200.f)
			->set_radius(80.f)
			->set_missile_speed(1700.f)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Low)
			->set_is_dangerous(false)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes });
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Ezreal, "Ezreal R");
		r_data->set_spell_hashes({ spell_hash("EzrealR") })
			->set_object_names({ "EzrealR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(20000.f)
			->set_radius(160.f)
			->set_delay(1.f)
			->set_missile_speed(2000.f)
			->set_danger_level(DangerLevel::Medium)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_is_range_fixed(true)
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