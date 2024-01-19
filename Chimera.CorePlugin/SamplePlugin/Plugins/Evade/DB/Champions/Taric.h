#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/SpellDetector.h"
#include "../../SpellDetector/DetectedSpells/DetectedLine.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

// TODO: E end_pos & on_process_spell
class Taric
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Taric, "Taric E");
		e_data
			->set_spell_hashes({ spell_hash("TaricE") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_start_pos_from_unit(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(1.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(70.0f)
			->set_range(600.0f)
			->set_on_process_spell([e_data](SpellCastInfo* spell)
			{
				for (const auto& champion : entities->get_heroes())
				{
					if (champion->is_ally()) 
						continue;

					if (!champion->has_buff(buff_hash("taricwleashactive"))) 
						continue;

					DetectedSpell* detected_spell = new DetectedLine(e_data, spell->get_start_pos().to_2d(), spell->get_end_pos().to_2d());
					detected_spell->source = champion;
					detected_spell->direction = (detected_spell->original_end_pos - detected_spell->source->get_position().to_2d()).normalized();
					detected_spell->cast_time = game_time->get_time();
					detected_spell->end_time = detected_spell->cast_time + e_data->delay(detected_spell);

					Evade::SpellDetector::detected_spells.push_back(detected_spell);
				}
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