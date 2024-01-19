#pragma once
#include "../EvadeSpellData.h"

class Brand
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Brand, "Brand Q");
		q_data->set_spell_hashes({ spell_hash("BrandQ") })
			->set_object_names({ "BrandQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1100.f)
			->set_radius(60.f)
			->set_missile_speed(1600.f)
			->set_danger_level(DangerLevel::High)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_is_dangerous(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Brand, "Brand W");
		w_data->set_spell_hashes({ spell_hash("BrandW") })
			->set_type(EvadeSpellType::Circle)
			->set_range(900.f)
			->set_radius(260.f)
			->set_delay(.877f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);
		spells.push_back(w_data);
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