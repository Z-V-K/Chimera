#pragma once
#include "../DamageChamp.h"

class Singed : public DamageChamp
{
public:
    Singed(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const std::pair<double, double> EDamage[5] =
        {
            { 50, 6   },
            { 60, 6.5 },
            { 70, 7   },
            { 80, 7.5 },
            { 90, 8   }
        };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.1125 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {

        }

        if (spellslot == SlotId::E)
        {
            ret.magical = EDamage[level].first + EDamage[level].second * target->get_max_health() + 0.6 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {

        }

        return ret;
    }
};