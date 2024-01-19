#pragma once
#include "../EvadeSpellData.h"

class Lux
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Lux, "Lux Q");
		q_data->set_spell_hashes({ spell_hash("LuxLightBinding") })
			->set_object_names({ "LuxLightBindingMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::YasuoWall }) // TODO Q2 on minion/hero
			->set_range(1300.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Lux, "Lux E");
		e_data->set_spell_hashes({ spell_hash("LuxLightStrikeKugel") })
			->set_object_names({ "LuxLightStrikeKugel" }) // TODO; ground
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(310.0f)
			->set_range(1100.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Lux, "Lux R");
		r_data->set_spell_hashes({ spell_hash("LuxRMis") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(1.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(100.0f)
			->set_range(3400.0f);
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