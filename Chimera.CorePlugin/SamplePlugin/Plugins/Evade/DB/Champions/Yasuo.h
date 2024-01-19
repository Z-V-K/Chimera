#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Yasuo
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Yasuo, "Yasuo Q");
		q_data
			->set_spell_hashes({ spell_hash("YasuoQ1Wrapper"), spell_hash("YasuoQ2Wrapper") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(FLT_MAX)
			->set_radius(40.0f)
			->set_range(450.0f)
			->set_add_bounding(true)
			->set_delay([](DetectedSpell* spell)
				{
					float bonus_atk_speed = spell->source->get_attack_speed_multiplier() - 1.0f;
					return std::max(0.35f - 0.035f * bonus_atk_speed, 0.175f);
				});
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Yasuo, "Yasuo Q3");
		q_data
			->set_spell_hashes({ spell_hash("YasuoQ3Wrapper") })
			->set_object_names({ "YasuoQ3Mis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(90.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1150.0f)
			->set_delay([](DetectedSpell* spell)
				{
					float bonus_atk_speed = spell->source->get_attack_speed_multiplier() - 1.0f;
					return std::max(0.35f - 0.035f * bonus_atk_speed, 0.28f);
				});
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