#pragma once
#include "../DamagePassive.h"

struct BelvethPassive : DamagePassive
{
	BelvethPassive() : DamagePassive(CharacterHash::Belveth) { }

    double damages[3]
    {
        4.5,
        6.0,
        7.5
    };

	double maxmobdamages[3]
    {
        45.0,
        60.0,
        75.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        const int buffCount = target->get_buff_count(0x43a90796);
        if (buffCount <= 0)
            return { 0.0, 0.0, 0.0 };
        const int index = source->get_spell(SlotId::R)->get_level() - 1;
        const double damage = damages[index];
        const double ret = target->is_minion() && target->is_neutral() ? std::min(damage * (double)std::min(10, buffCount), maxmobdamages[index]) : damage * (double)buffCount;

        return { 0.0, 0.0, ret };
	}

    bool is_active(GameObject* source, GameObject* target) override
	{
        return target->has_buff(0x43a90796);
	}
};