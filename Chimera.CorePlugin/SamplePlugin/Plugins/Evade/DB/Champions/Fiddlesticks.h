#pragma once
#include "../EvadeSpellData.h"

class Fiddlesticks
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Fiddlesticks, "Fiddlesticks E");
		e_data->set_spell_hashes({ spell_hash("FiddleSticksE") })
			->set_type(EvadeSpellType::CustomPolygon)
			->set_delay(.4f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_is_range_limited(true)
			->set_range(850.f)
			->set_is_hard_cc(true);

		e_data->custom_polygon = [](DetectedSpell* spell)
		{
			const auto end_pos = spell->get_end_pos();
			const auto direction = spell->direction;
			const auto perp_direction = direction.perpendicular();
			const auto height = local_player->get_position().y;

			Geometry::Rectangle rect{
				end_pos.extend(end_pos + perp_direction, -400.f).to_3d(height),
				end_pos.extend(end_pos + perp_direction, 400.f).to_3d(height),
				150.f };

			return rect.to_polygon();
		};
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Fiddlesticks, "Fiddlesticks R");
		r_data->set_spell_hashes({ spell_hash("FiddleSticksR") })
			->set_type(EvadeSpellType::Circle)
			->set_delay(1.5f)
			->set_radius(600.f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_is_range_limited(true)
			->set_range(800.f)
			->set_is_hard_cc(true);
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