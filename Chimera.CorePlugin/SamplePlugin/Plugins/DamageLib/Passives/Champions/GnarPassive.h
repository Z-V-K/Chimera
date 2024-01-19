#pragma once
#include "../DamagePassive.h"

struct GnarPassive : DamagePassive
{
	GnarPassive() : DamagePassive(CharacterHash::Gnar) { }

    double damages[5]
    {
        0.0,
        10.0,
        20.0,
        30.0,
        40.0
    };
    double damagePercents[5]
    {
        0.06,
        0.08,
        0.1,
        0.12,
        0.14
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        DamageOutput ret;

        auto spell = source->get_spell(SlotId::W);
        if (!spell || spell->get_level() <= 0)
            return ret;

        double damage = damages[spell->get_level() - 1] + damagePercents[spell->get_level() - 1] * (double)target->get_max_health() + (double)source->get_total_ad();
        if (target->is_minion() && target->is_neutral())
            damage = std::min(300.0 + (double)source->get_total_ad(), damage);

        ret.magical += damage;

        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_buff_count(0x94872ca4) == 2;
	}
};