#pragma once
#include "../DamageChamp.h"

class Taric : public DamageChamp
{
public:
    Taric(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::E)
        {
            ret.magical = W->base_damage[level] + 0.5 * src->get_ap() + 0.5 * src->get_bonus_armor();
        }

        return ret;
    }
};