#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Kayle
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Kayle, "Kayle Q");
		q_data->set_spell_hashes({ spell_hash("KayleQ") })
			->set_object_names({ "KayleQMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(1600.0f)
			->set_radius(75.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(900.0f)
			->set_delay([](DetectedSpell* spell)
			{
				return spell->source ? spell->source->get_attack_delay() : .25f;
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Kayle, "Kayle R");
		r_data->set_spell_hashes({ spell_hash("KayleR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(2.5f)
			->set_missile_speed(FLT_MAX)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_radius([] (DetectedSpell* spell)
			{
				return spell->source->get_spell(SlotId::R)->get_level() == 3 ? 775.f : 675.f;
			})
			->set_end_position([](DetectedSpell* spell)
			{
				return spell->target ? spell->target->get_position().to_2d() : spell->source->get_position().to_2d();
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
