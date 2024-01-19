#pragma once
#include "../DamageChamp.h"

class RekSai : public DamageChamp
{
public:
    RekSai(GameObject* source) : DamageChamp(source) { }

    double QDamage[5]           = { 21, 27, 33, 39, 45 };
    double QDamageBurrowed[5]   = { 60, 95, 130, 165, 200 };
    double WDamageBurrowed[5]   = { 55, 70, 85, 100, 115 };
    double EDamage[5]           = { 55, 60,65, 70, 75 };
    std::pair<double, double> RDamage[3] = {
        {100, 0.2},
        {250, 0.25},
        {400, 0.3}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = QDamage[level] + 0.5 * src->get_bonus_ad();

            if (stage == 2)
                ret.physical = QDamageBurrowed[level] + 0.5 * src->get_bonus_ad() + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = WDamageBurrowed[level] + 0.8 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            double damage = EDamage[level] + 0.85 * src->get_bonus_ad();

            if (stage == 1)
                ret.physical = damage;

            if (stage == 2)
                ret.physical = damage * 2;
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = RDamage[level].first + 1.75 * src->get_bonus_ad() + RDamage[level].second * (target->get_max_health() - target->get_health());
        }

        return ret;
    }
};