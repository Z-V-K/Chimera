#pragma once
#include "../DamageChamp.h"

class Poppy : public DamageChamp
{
public:
    Poppy(GameObject* source) : DamageChamp(source) { }

    double qDamages[5]
    {
        40.0,
        60.0,
        80.0,
        100.0,
        120.0
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = qDamages[level] + .89 * src->get_bonus_ad() + .08 * target->get_max_health();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = Q->base_damage[level] + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = W->base_damage[level] + 0.5 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + .9 * src->get_bonus_ad();
        }

        return ret;
    }
};