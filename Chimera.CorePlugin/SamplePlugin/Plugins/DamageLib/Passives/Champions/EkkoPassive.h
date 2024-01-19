#pragma once
#include "../DamagePassive.h"

struct EkkoPassive : DamagePassive
{
	EkkoPassive() : DamagePassive(CharacterHash::Ekko) { }

    double damages[18]
    {
        30.0,
        40.0,
        50.0,
        60.0,
        70.0,
        80.0,
        85.0,
        90.0,
        95.0,
        100.0,
        105.0,
        110.0,
        115.0,
        120.0,
        125.0,
        130.0,
        135.0,
        140.0
    };

    double edamages[5]
    {
        50.0,
        75.0,
        100.0,
        125.0,
        150.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        DamageOutput ret{ 0.0, 0.0, 0.0 };
        if (target->get_buff_count(0x346e7902) == 2)
        {
            double damage = damages[std::min(17, std::max(0, source->get_level() - 1))] + 0.9 * (double)source->get_ap();
            if (target->is_minion() && target->is_neutral())
                damage *= 2.5;

            ret.magical += damage;
        }

        if (target->get_health_percent() < 30.0)
        {
            auto spell = source->get_spell(SlotId::W);
            if (spell && spell->get_level() > 0)
            {
                double damage = 0.0;

                if (target->is_hero())
                    damage = std::max(.03 + .03 * (source->get_ap() / 100.0), 15.0);
                if (target->is_minion())
                    damage = std::min(std::max(.03 + .03 * (source->get_ap() / 100.0), 15.0), 150.0);

                ret.magical += damage;
            }
        }

        if (source->has_buff(0xb8e2251b))
        {
            auto spell = source->get_spell(SlotId::E);

            if (spell && spell->get_level() > 0)
            {
                ret.magical += edamages[std::min(spell->get_level() - 1, 4)] + .4 * source->get_ap();
            }
        }

        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_buff_count(0x346e7902) == 2 || target->get_health_percent() < 30.0 || source->has_buff(0xb8e2251b);
	}
};