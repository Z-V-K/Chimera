#pragma once
#include "../EvadeSpellData.h"

class Hecarim
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
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Hecarim, "Hecarim R Horses");
		r_data->set_object_names({ "HecarimUltMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.f)
			->set_missile_speed(1100.f)
			->set_radius(50.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(1000.f);
		spells.push_back(r_data);

		r_data = new EvadeSpellData(CharacterHash::Hecarim, "Hecarim R Fear");
		r_data->set_spell_hashes({ spell_hash("HecarimUlt") })
			->set_missile_speed(1100.f)
			->set_type(EvadeSpellType::Circle)
			->set_radius(315 / 2.f)
			->set_add_bounding(true)
			->set_is_range_min(true)
			->set_min_range(300.f)
			->set_range(1000.f)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_delay([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
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