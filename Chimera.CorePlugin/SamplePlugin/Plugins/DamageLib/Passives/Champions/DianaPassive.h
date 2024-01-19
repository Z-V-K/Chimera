#pragma once
#include "../DamagePassive.h"

struct DianaPassive : DamagePassive
{
	DianaPassive() : DamagePassive(CharacterHash::Diana) { }

    double damages[18]
    {
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
        110.0,
        125.0,
        140.0,
        155.0,
        170.0,
        195.0,
        220.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        double num = damages[std::min(source->get_level() - 1, 17)] + 0.5 * (double)source->get_ap();
        num = target->is_minion() && target->is_neutral() ? num * 3.0 : num;

        return { num, 0.0, 0.0 };
	}

    bool is_active(GameObject* source, GameObject* target) override
	{
        return source->has_buff(0x6495f7ef);
	}
};