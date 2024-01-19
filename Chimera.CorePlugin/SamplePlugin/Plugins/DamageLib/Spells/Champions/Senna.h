#pragma once
#include "../DamageChamp.h"

class Senna : public DamageChamp
{
public:
    Senna(GameObject* source) : DamageChamp(source)
    {
        Q->has_on_hit = true;
    }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 0.5 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = W->base_damage[level] + 0.7 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 1.15 * src->get_bonus_ad() + 0.7 * src->get_ap();
        }

        return ret;
    }
};