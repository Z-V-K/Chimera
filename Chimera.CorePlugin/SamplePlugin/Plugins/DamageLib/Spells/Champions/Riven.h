#pragma once
#include "../DamageChamp.h"

class Riven : public DamageChamp
{
public:
    Riven(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QDamage[5] = {
        {15, 0.45},
        {35, 0.50},
        {55, 0.55},
        {75, 0.60},
        {95, 0.65}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level].first + QDamage[level].second * src->get_total_ad();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = W->base_damage[level] + 1.1 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            double missingHealthPercentage = 100 * (1 - src->get_health() / src->get_max_health());
            double missingHealthBonus = (missingHealthPercentage < 0.75 ? missingHealthPercentage * 0.02667 : 2.0);

            ret.physical = (R->base_damage[level] + 0.6 * src->get_bonus_ad()) * (1 + missingHealthBonus);
        }

        return ret;
    }
};