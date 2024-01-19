#pragma once
#include "../DamageChamp.h"

class Olaf : public DamageChamp
{
public:
    Olaf(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            ret.raw = E->base_damage[level] + 0.5 * src->get_total_ad();
        }

        return ret;
    }
};