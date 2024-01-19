#pragma once
#include "../DamageChamp.h"

class Rengar : public DamageChamp
{
public:
    Rengar(GameObject* source) : DamageChamp(source) { }

    double QDamage[5]
    {
       30.0,
       60.0,
       90.0,
       120.0,
       150.0
    };

    double QDamagePercents[5]
    {
        0.0,
        0.05,
        0.1,
        0.15,
        0.2
    };

    double Q2Damages[18]
    {
        30.0,
        45.0,
        60.0,
        75.0,
        90.0,
        105.0,
        120.0,
        135.0,
        150.0,
        160.0,
        170.0,
        180.0,
        190.0,
        200.0,
        210.0,
        220.0,
        230.0,
        240.0
    };

    double WDamage[5]
    {
        50.0,
        80.0,
        110.0,
        140.0,
        170.0
    };

    double W2Damage[18]
    {
        50.0,
        60.0,
        70.0,
        80.0,
        90.0,
        100.0,
        110.0,
        120.0,
        130.0,
        140.0,
        150.0,
        160.0,
        170.0,
        180.0,
        190.0,
        200.0,
        210.0,
        220.0
    };

    double EDamage[5]
    {
        55.0,
        100.0,
        145.0,
        190.0,
        235.0
    };

    double E2Damage[18]
    {
        50.0,
        65.0,
        80.0,
        95.0,
        110.0,
        125.0,
        140.0,
        155.0,
        170.0,
        185.0,
        200.0,
        215.0,
        230.0,
        245.0,
        260.0,
        275.0,
        290.0,
        305.0
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = QDamage[level] + QDamagePercents[level] * src->get_total_ad();

            if (stage == 2)
                ret.physical = Q2Damages[std::min(src->get_level() - 1, 17)] + .4 * src->get_total_ad();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.magical = WDamage[level] + .8 * src->get_ap();
            if (stage == 2)
                ret.magical = W2Damage[std::min(src->get_level() - 1, 17)] + .8 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.physical = EDamage[level] + .8 * src->get_bonus_ad();
            if (stage == 2)
                ret.physical = E2Damage[std::min(src->get_level() - 1, 17)] + .8 * src->get_bonus_ad();
        }

        return ret;
    }
};