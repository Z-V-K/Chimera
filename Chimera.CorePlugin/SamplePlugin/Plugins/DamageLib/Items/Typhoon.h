#pragma once
#include "DamageItem.h"

struct Typhoon : DamageItem
{
	Typhoon() : DamageItem(ItemId::Typhoon, DamageType::Physical) { }

	double damages[18]
	{
		50 * 3,
		50 * 3,
		50 * 3,
		50 * 3,
		50 * 3,
		50 * 3,
		50 * 3,
		56.06 * 3,
		62.12 * 3,
		68.18 * 3,
		74.24 * 3,
		80.30 * 3,
		86.36 * 3,
		92.42 * 3,
		98.48 * 3,
		104.55 * 3,
		110.61 * 3,
		116.67 * 3
	};

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		double damage = damages[std::min(source->get_level() - 1, 17)] + .45 * source->get_bonus_ad();

		double pct_missing = (int)((((target->get_max_health() - target->get_health()) / target->get_max_health()) * 100) / 7.5);
		pct_missing = std::min(.75, pct_missing);

		return { 0.0, damage + ((.05 * pct_missing) * damage), 0.0 };
	}

	DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { };
	}
};