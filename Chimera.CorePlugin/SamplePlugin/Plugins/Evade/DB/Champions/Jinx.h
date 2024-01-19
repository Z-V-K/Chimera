#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Jinx
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Jinx, "Jinx W");
		w_data->set_spell_hashes({ spell_hash("JinxW") })
			->set_object_names({ "JinxWMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1500.f)
			->set_radius(50.f)
			->set_delay(.6f)
			->set_delay([](DetectedSpell* spell)
			{
				if (!spell->source)
					return .45f;

				const auto bonus_as = spell->source->get_attack_speed_multiplier() - 1.f;
				return std::max(.4f, .6f - (bonus_as * .25f));
			});
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Jinx, "Jinx E");
		//
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Jinx, "Jinx R");
		r_data->set_spell_hashes({ spell_hash("JinxR") })
			->set_object_names({ "JinxR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.6f)
			->set_missile_speed(1700.f) // TODO; acceleration: 2200 after 1350 units
			->set_radius(140.f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(20000.f);
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