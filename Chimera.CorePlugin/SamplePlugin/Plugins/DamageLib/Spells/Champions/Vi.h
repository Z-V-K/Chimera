#pragma once
#include "../DamageChamp.h"

class Vi : public DamageChamp
{
public:
    Vi(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 0.8 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 1.2 * src->get_total_ad() + src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 1.1 * src->get_bonus_ad();
        }

        return ret;
    }
};