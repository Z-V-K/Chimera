#pragma once
#include "../DamageChamp.h"

class Rakan : public DamageChamp
{
public:
    Rakan(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.8 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.5 * src->get_ap();
        }

        return ret;
    }
};