#pragma once
#include "../EvadeSpellData.h"

class Heimerdinger
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Heimerdinger, "Heimerdinger W");
		w_data
			->set_object_names({ "HeimerdingerWAttack2", "HeimerdingerWAttack2Ult" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1325.f)
			->set_radius(60.f)
			->set_missile_speed(1650.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_is_dangerous(true);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Heimerdinger, "Heimerdinger E");
		e_data->set_spell_hashes({ spell_hash("HeimerdingerE") })
			->set_object_names({ "HeimerdingerESpell" })
			->set_type(EvadeSpellType::Circle)
			->set_range(970.f)
			->set_radius(250.f)
			->set_missile_speed(1200.f)
			->set_danger_level(DangerLevel::High)
			->set_is_hard_cc(true)
			->set_is_dangerous(true);
		spells.push_back(e_data);

		e_data = new EvadeSpellData(CharacterHash::Heimerdinger, "Heimerdinger E ult");
		e_data->set_spell_hashes({ spell_hash("HeimerdingerEUlt") })
			->set_object_names({ "HeimerdingerESpell_ult" })
			->set_type(EvadeSpellType::Circle)
			->set_range(925.f)
			->set_radius(150.f)
			->set_is_range_limited(true)
			->set_missile_speed(1200.f)
			->set_danger_level(DangerLevel::High)
			->set_is_hard_cc(true)
			->set_is_dangerous(true);
		spells.push_back(e_data);

		e_data = new EvadeSpellData(CharacterHash::Heimerdinger, "Heimerdinger E ult bounce");
		e_data->set_object_names({ "HeimerdingerESpell_ult2", "HeimerdingerESpell_ult3" })
			->set_type(EvadeSpellType::Circle)
			->set_range(1075.f)
			->set_radius(150.f)
			->set_missile_speed(1400.f)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_is_hard_cc(true);
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