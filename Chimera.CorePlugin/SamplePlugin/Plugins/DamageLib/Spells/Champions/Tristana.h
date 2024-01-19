#pragma once
#include "../DamageChamp.h"

class Tristana : public DamageChamp
{
public:
    Tristana(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> EDamage[5] =
    {
        { 70,  0.5  },
        { 80,  0.75 },
        { 90,  1.0  },
        { 100, 1.25 },
        { 110, 1.5  }
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.5 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = EDamage[level].first + EDamage[level].second * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + src->get_ap();
        }

        return ret;
    }
};