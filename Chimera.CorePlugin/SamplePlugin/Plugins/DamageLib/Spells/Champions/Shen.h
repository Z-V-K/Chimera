#pragma once
#include "../DamageChamp.h"

class Shen : public DamageChamp
{
public:
    Shen(GameObject* source) : DamageChamp(source) { }

    double QDamage[18]
    {
        10.0,
        10.0,
        10.0,
        16.0,
        16.0,
        16.0,
        22.0,
        22.0,
        22.0,
        28.0,
        28.0,
        28.0,
        34.0,
        34.0,
        34.0,
        40.0,
        40.0,
        40.0
    };

    double QDamagePercent[5]
    {
        0.02,
        0.025,
        0.03,
        0.035,
        0.04
    };

    double Q2DamagePercent[5]
    {
        0.05,
        0.055,
        0.06,
        0.065,
        0.07
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.magical = QDamage[std::min(17, src->get_level() - 1)] + (QDamagePercent[level] + 0.015 * (double)src->get_ap() / 100.0) * (double)target->get_max_health();
            if (stage == 2)
                ret.magical = QDamage[std::min(17, src->get_level() - 1)] + (Q2DamagePercent[level] + 0.02 * (double)src->get_ap() / 100.0) * (double)target->get_max_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.15 * src->get_bonus_health();
        }

        return ret;
    }
};