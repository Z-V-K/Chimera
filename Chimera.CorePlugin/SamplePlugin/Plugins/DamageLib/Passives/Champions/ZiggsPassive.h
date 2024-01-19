#pragma once
#include "../DamagePassive.h"

struct ZiggsPassive : DamagePassive
{
	ZiggsPassive() : DamagePassive(CharacterHash::Ziggs) { }

    double damages[18]
    {
        20.0,
        24.0,
        28.0,
        32.0,
        36.0,
        40.0,
        48.0,
        56.0,
        64.0,
        72.0,
        80.0,
        88.0,
        100.0,
        112.0,
        124.0,
        136.0,
        148.0,
        160.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        return { 0.5 * (double)source->get_ap() + damages[std::min(17, std::max(0, source->get_level() - 1))] * (target->is_turret() ? 2.5 : 1.0), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x1671b3c6);
	}
};