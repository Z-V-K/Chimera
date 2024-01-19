#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Soraka
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Soraka, "Soraka Q");
		q_data
			->set_spell_hashes({ spell_hash("SorakaQ") })
			//->set_object_names({ "SorakaQMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1350.0f)
			->set_radius(265.0f)
			->set_range(800.0f)
			->set_delay([](DetectedSpell* spell)
			{
				const auto range = spell->get_range();

				if (range <= 50.f)
					return .25f;

				return std::min(1.f, .25f + .05f * (int)(range / 50));
			});
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Soraka, "Soraka E");
		e_data
			->set_spell_hashes({ spell_hash("SorakaE") })
			//->set_object_names({ "SorakaQMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_duration(1.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(260.0f)
			->set_range(925.0f);
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