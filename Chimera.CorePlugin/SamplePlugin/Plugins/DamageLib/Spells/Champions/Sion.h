#pragma once
#include "../DamageChamp.h"

class Sion : public DamageChamp
{
public:
    Sion(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> QDamage[5] =
    {
        { 40,  0.45  },
        { 60,  0.525 },
        { 80,  0.60  },
        { 100, 0.675 },
        { 120, 0.75  }
    };

    const std::pair<double, double> WDamage[5] =
    {
        { 45,  0.10 },
        { 65,  0.11 },
        { 90,  0.12 },
        { 115, 0.13 },
        { 140, 0.14 }
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            double dmgMod = (target->is_minion() ? 0.6 : (target->is_jungle_minion() ? 1.5 : 1.0));
            ret.physical = dmgMod * (QDamage[level].first + QDamage[level].second * src->get_total_ad());
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = WDamage[level].first + 0.4 * src->get_ap() + WDamage[level].second * target->get_max_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.55 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 0.4 * src->get_bonus_ad();
        }

        return ret;
    }
};