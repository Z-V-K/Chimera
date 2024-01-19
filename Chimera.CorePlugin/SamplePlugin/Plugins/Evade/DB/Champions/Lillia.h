#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Lillia
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Lillia, "Lillia Q");
		q_data->set_spell_hashes({ spell_hash("LilliaQ") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(485.0f)
			->set_range(485.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Lillia, "Lillia W");
		w_data->set_spell_hashes({ spell_hash("LilliaW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.759f)
			->set_missile_speed(FLT_MAX)
			->set_radius(250.0f)
			->set_range(500.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Lillia, "Lillia E");
		e_data->set_spell_hashes({ spell_hash("LilliaE") })
			->set_object_names({ "LilliaERollingMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.4f)
			->set_missile_speed(1400.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range([] (DetectedSpell* spell)
			{
				if (spell->missile)
					return spell->missile->get_missile_client()->get_start_position().distance(spell->missile->get_missile_client()->get_end_position());
				return 5000.f;
			});
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
