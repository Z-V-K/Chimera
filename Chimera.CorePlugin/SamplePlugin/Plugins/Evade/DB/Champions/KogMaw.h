#pragma once
#include "../EvadeSpellData.h"

class KogMaw
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::KogMaw, "KogMaw Q");
		q_data->set_spell_hashes({ spell_hash("KogMawQ") })
			->set_object_names({ "KogMawQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1650.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1200.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::KogMaw, "KogMaw E");
		e_data->set_spell_hashes({ spell_hash("KogMawVoidOoze") })
			->set_object_names({ "KogMawVoidOozeMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(1400.0f)
			->set_radius(120.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1350.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::KogMaw, "KogMaw R");
		r_data->set_spell_hashes({ spell_hash("KogMawLivingArtillery") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(1.2f)
			->set_missile_speed(FLT_MAX)
			->set_radius(240.0f)
			->set_range(1800.0f);
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