#pragma once
#include "../EvadeSpellData.h"

class Ashe
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Ashe, "Ashe W");
		w_data->set_spell_hashes({ spell_hash("Volley"), spell_hash("VolleyRank2"), spell_hash("VolleyRank3"), spell_hash("VolleyRank4"), spell_hash("VolleyRank5") })
			->set_object_names({ "VolleyAttack", "VolleyAttackWithSound" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1300.f)
			->set_radius(20.f)
			->set_missile_speed(1600.f)
			->set_danger_level(DangerLevel::Low)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_offset_start(100.f)
			->set_skip_distance_check(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_multiple_number([] (GameObject* source, SpellCastInfo* spell)
			{
				return 6 + source->get_spell(SlotId::W)->get_level();
			})
			->set_multiple_angle(5.f * M_PI / 180.f);

		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Ashe, "Ashe R");
		r_data->set_spell_hashes({ spell_hash("EnchantedCrystalArrow") })
			->set_object_names({ "EnchantedCrystalArrow" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_range(25000.f)
			->set_radius(130.f)
			->set_missile_speed(1500.f)
			->set_danger_level(DangerLevel::Extreme)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall });
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