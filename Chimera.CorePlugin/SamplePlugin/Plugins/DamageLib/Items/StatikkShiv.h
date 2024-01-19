#pragma once
#include "DamageItem.h"

struct StatikkShiv : DamageItem
{
	StatikkShiv() : DamageItem(ItemId::Statikk_Shiv, DamageType::Magical) { }

	double damages[18]
	{
        100.0,
        100.0,
        100.0,
        100.0,
        100.0,
        100.0,
        110.0,
        120.0,
        130.0,
        140.0,
        145.0,
        150.0,
        155.0,
        160.0,
        165.0,
        170.0,
        175.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
        return { target->is_minion() ? 200 : damages[std::min(17, source->get_level() - 1)] + 0.15 * (double)source->get_ap(), 0.0, 0.0};
	}

    bool is_active(GameObject* source, GameObject* target) override
	{
        return source->get_buff_count(0xc4266ca1) == 100;
	}
};