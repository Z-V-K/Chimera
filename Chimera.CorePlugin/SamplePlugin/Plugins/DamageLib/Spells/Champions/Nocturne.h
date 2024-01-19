#pragma once
#include "../DamageChamp.h"

class Nocturne : public DamageChamp
{
public:
    Nocturne(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        double ETickDamage[5] = { 20, 31.25, 42.5, 53.75, 65 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 0.85 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = ETickDamage[level] + 0.25 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 1.2 * src->get_bonus_ad();
        }

        return ret;
    }
};