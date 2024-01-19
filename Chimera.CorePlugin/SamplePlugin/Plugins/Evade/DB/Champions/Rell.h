#pragma once
#include "../EvadeSpellData.h"

class Rell
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Rell, "Rell Q");
		q_data
			->set_spell_hashes({ spell_hash("RellQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.35f)
			->set_range(430.0f + 220.0f)
			->set_radius(75.0f)
			->set_offset_start(-220.0f)
			->set_missile_speed(FLT_MAX);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Rell, "Rell W");
		w_data
			->set_spell_hashes({ spell_hash("RellW_Dismount") })
			->set_type(EvadeSpellType::CustomPolygon)
			->set_add_bounding(true)
			->set_is_range_limited(true)
			->set_min_range(100.f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.625f)
			->set_range(400.0f);

		w_data->custom_polygon = [](DetectedSpell* spell)
		{
			const auto end_pos = spell->get_end_pos();
			const auto direction = spell->direction;
			const auto height = local_player->get_position().y;
			return Geometry::Rectangle{
				end_pos.extend(end_pos + direction, 500.f).to_3d(height),
				end_pos.extend(end_pos + direction, -200.f).to_3d(height),
				250.f }.to_polygon();
		};
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Rell, "Rell R");
		r_data
			->set_spell_hashes({ spell_hash("RellR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(450.0f) // initial explosion radius
			->set_range(375.0f);
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