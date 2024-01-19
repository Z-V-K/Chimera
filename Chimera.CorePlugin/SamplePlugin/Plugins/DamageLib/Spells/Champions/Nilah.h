#pragma once
#include "../DamageChamp.h"

class Nilah : public DamageChamp
{
public:
    Nilah(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QDamage[5] =
    {
        { 5,  0.9   },
        { 10, 0.975 },
        { 15, 1.05  },
        { 20, 1.125 },
        { 25, 1.2   }
    };

    double RBaseDamage[3] = { 125, 225, 325 };
    double RTickDamage[3] = { 15, 30, 45 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical =QDamage[level].first + QDamage[level].second * src->get_total_ad();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.2 * src->get_total_ad();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.physical = RBaseDamage[level] + 1.2 * src->get_bonus_ad();

            if (stage == 2)
                ret.physical = RTickDamage[level] + 0.28 * src->get_bonus_ad();
        }

        return ret;
    }
};