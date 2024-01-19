#pragma once
#include "../DamageChamp.h"

class Varus : public DamageChamp
{
public:
    Varus(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> QDamage[5] =
    {
        {10, 0.8333},
        {46.67, 0.8668},
        {83.33, 0.9},
        {120, 0.9333 },
        {156.75, 0.9667}
    };

    double WDamage[5]
    {
        0.03,
        0.035,
        0.04,
        0.045,
        0.05
    };

    double EDamage[5]
    {
        60.0,
        100.0,
        140.0,
        180.0,
        220.0
    };

    double RDamage[3]
    {
        150.0,
        250.0,
        350.0
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level].first * QDamage[level].second * src->get_total_ad();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = (WDamage[level] + .02 * src->get_ap() / 100) * src->get_max_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = EDamage[level] + .9 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = RDamage[level] + 1 * src->get_ap();
        }

        return ret;
    }
};