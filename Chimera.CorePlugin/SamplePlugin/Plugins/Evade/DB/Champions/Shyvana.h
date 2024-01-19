#pragma once
#include "../EvadeSpellData.h"

class Shyvana
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Shyvana, "Shyvana E");
		e_data
			->set_spell_hashes({ spell_hash("ShyvanaFireball") })
			->set_object_names({ "ShyvanaFireballMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(925.0f);
		spells.push_back(e_data);

		e_data = new EvadeSpellData(CharacterHash::Shyvana, "Shyvana E Dragon");
		e_data
			->set_spell_hashes({ spell_hash("ShyvanaFireballDragon2") })
			->set_object_names({ "ShyvanaFireballDragonMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.33f)
			->set_missile_speed(1575.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(925.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Shyvana, "Shyvana R");
		r_data
			->set_spell_hashes({ spell_hash("ShyvanaTransformCast") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1100.0f)
			->set_radius(160.0f)
			->set_is_dash(true)
			->set_range(850.0f);
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