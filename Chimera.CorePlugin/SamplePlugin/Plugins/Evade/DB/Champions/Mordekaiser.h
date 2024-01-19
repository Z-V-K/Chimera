#pragma once
#include "../EvadeSpellData.h"

class Mordekaiser
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Mordekaiser, "Mordekaiser Q");
		q_data->set_spell_hashes({ spell_hash("MordekaiserQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(false)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(160.0f) // 80 wiki
			->set_range(625.0f); // 622 wiki
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Mordekaiser, "Mordekaiser E");
		e_data->set_spell_hashes({ spell_hash("MordekaiserE") })
			->set_type(EvadeSpellType::CustomPolygon)
			->set_add_bounding(false)
			->set_is_dangerous(true)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(.75f)
			->set_missile_speed(3000.0f)
			->set_radius(200.0f)
			->set_range(700.0f);

		e_data->custom_polygon = [](DetectedSpell* spell)
			{
				const auto height = local_player->get_position().y;
				const auto start_pos = (spell->cached_end_pos + spell->direction * (-600.f)).to_3d(height);
				const auto end_pos = (spell->cached_end_pos + spell->direction * 275.f).to_3d(height);

				return Geometry::Rectangle{ start_pos, end_pos, 150.f }.to_polygon();
			};
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