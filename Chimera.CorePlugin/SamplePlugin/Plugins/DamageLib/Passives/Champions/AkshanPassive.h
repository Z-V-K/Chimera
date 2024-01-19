#pragma once
#include "../DamagePassive.h"

struct AkshanPassive : DamagePassive
{
    AkshanPassive() : DamagePassive(CharacterHash::Akshan) { }

    double damages[18]
    {
        10.0,
        15.0,
        20.0,
        25.0,
        30.0,
        35.0,
        40.0,
        45.0,
        55.0,
        65.0,
        75.0,
        85.0,
        95.0,
        105.0,
        120.0,
        135.0,
        150.0,
        165.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        const double val = damages[std::min(source->get_level() - 1, 17)] + 0.6 * (double)source->get_ap();

        return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0xc6aed6a4) == 2;
	}
};