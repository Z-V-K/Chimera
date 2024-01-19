#pragma once
#include "../DamageChamp.h"

class Volibear : public DamageChamp
{
public:
    Volibear(GameObject* source) : DamageChamp(source)
    {
        W->has_on_hit = true;
    }

    const std::pair<double, double> EDamage[5] =
    {
        {80, 0.11},
        {110, 0.12},
        {140, 0.13},
        {170, 0.14},
        {200, 0.15}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 1.2 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = W->base_damage[level] + src->get_total_ad() + 0.06 * src->get_bonus_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = EDamage[level].first + 0.8 * src->get_ap() + EDamage[level].second * target->get_max_health();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 2.5 * src->get_bonus_ad() + 1.25 * src->get_ap();
        }

        return ret;
    }
};