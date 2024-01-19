#pragma once
#include "DamageItem.h"

struct WitsEnd : DamageItem
{
	WitsEnd() : DamageItem(ItemId::Wits_End, DamageType::Magical) { }

	double damage[18]
	{
        15.0,
        15.0,
        15.0,
        15.0,
        15.0,
        15.0,
        15.0,
        15.0,
        25.0,
        35.0,
        45.0,
        55.0,
        65.0,
        75.0,
        76.25,
        77.5,
        78.75,
        80.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { damage[std::min(source->get_level() - 1, 17)], 0.0, 0.0};
	}
};