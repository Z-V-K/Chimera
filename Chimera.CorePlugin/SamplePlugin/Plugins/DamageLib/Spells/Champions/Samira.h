#pragma once
#include "../DamageChamp.h"

class Samira : public DamageChamp
{
public:
    Samira(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QDamage[5] = {
        {  0, 0.85},
        {  5, 0.95},
        { 10, 1.05},
        { 15, 1.15},
        { 20, 1.25}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        double missingHPPercentage = floor((10 * (1 - (target->get_health() / target->get_max_health()))));
        double magicBonus = (1 + missingHPPercentage * 0.1) * (src->get_level() + 1) + (0.035 + (0.07 / 17) * (src->get_level() - 1));

        if (spellslot == SlotId::Q)
        {
            double damage = QDamage[level].first + QDamage[level].second * src->get_total_ad();

            if (stage == 1)
            {
                ret.physical = damage;
                ret.magical  = magicBonus;
            }

            if (stage == 2)
                ret.physical = damage;
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = W->base_damage[level] + 0.8 * src->get_bonus_ad();
            ret.magical  = magicBonus;
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.2 * src->get_bonus_ad();
            ret.magical  = magicBonus;
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = (target->is_minion() ? 0.25 : 1.0) * R->base_damage[level] + 0.5 * src->get_total_ad();
        }

        return ret;
    }
};