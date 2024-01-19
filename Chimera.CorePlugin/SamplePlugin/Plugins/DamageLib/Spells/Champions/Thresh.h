#pragma once
#include "../DamageChamp.h"

class Thresh : public DamageChamp
{
public:
    Thresh(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const double EDamage[5] = { 75, 115, 155, 195, 235 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.9 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = EDamage[level] + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + src->get_ap();
        }

        return ret;
    }
};