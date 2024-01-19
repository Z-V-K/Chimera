#pragma once
#include "../EvadeSpellData.h"

class Syndra
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Syndra, "Syndra Q");
		q_data
			->set_spell_hashes({ spell_hash("SyndraQ"), spell_hash("SyndraQUpgrade") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_limited(true)
			->set_delay(0.6f)
			->set_missile_speed(FLT_MAX)
			->set_radius(210.0f)
			->set_range(800.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Syndra, "Syndra W");
		w_data
			->set_spell_hashes({ spell_hash("SyndraWCast") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			//->set_delay(0.0f)
			->set_missile_speed(1000.0f)
			->set_radius(225.0f)
			->set_range(950.0f)
			->set_delay([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Syndra, "Syndra E");
		e_data
			->set_spell_hashes({ spell_hash("SyndraE"), spell_hash("SyndraE5") })
			->set_type(EvadeSpellType::Cone)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(2500.0f)
			->set_radius([](DetectedSpell* spell)
			{
				return spell->source ? (spell->source->get_buff_count(buff_hash("syndrapassivestacks")) >= 80 ? 110.f : 75.f) : 56.f;
			})
			->set_range(750.0f);
		spells.push_back(e_data);
		// TODO; EQ
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