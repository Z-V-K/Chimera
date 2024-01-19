#pragma once
#include "../DamagePassive.h"

struct SettPassive : DamagePassive
{
	SettPassive() : DamagePassive(CharacterHash::Sett) { }

	double damages[5]
	{
		10.0,
		20.0,
		30.0,
		40.0,
		50.0
	};

	double damagePercents[5]
	{
		0.01,
		0.015,
		0.02,
		0.025,
		0.03
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Q);
		if (!spell || spell->get_level() == 0)
			return { };
		
		double val2 = damages[std::min(spell->get_level() - 1, 4)] + (damagePercents[std::min(spell->get_level() - 1, 4)] + 0.01 * (double)source->get_total_ad()) * (0.01 * (double)target->get_max_health());
		if (target->is_minion() && target->is_neutral())
			val2 = std::min(400.0, val2);

		return { 0.0, val2, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x677e78ac);
	}
};