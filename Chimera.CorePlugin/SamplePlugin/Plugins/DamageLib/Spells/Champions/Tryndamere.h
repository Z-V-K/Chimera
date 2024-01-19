#pragma once
#include "../DamageChamp.h"

class Tryndamere : public DamageChamp
{
public:
    Tryndamere(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 1.3 * src->get_bonus_ad() + 0.8 * src->get_ap();
        }

        return ret;
    }
};