#pragma once
#include "../DamageChamp.h"

class Sett : public DamageChamp
{
public:
    Sett(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QBonus[5] = {
        { 10, 0.010 },
        { 20, 0.015 },
        { 30, 0.020 },
        { 40, 0.025 },
        { 50, 0.030 }
    };

    std::pair<double, double> RDamage[3] = {
        { 200, 0.4 },
        { 300, 0.5 },
        { 400, 0.6 }
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            double bonusRatio = floor((src->get_total_ad() / 100));
            ret.physical = QBonus[level].first + (0.01 + bonusRatio * QBonus[level].second) * target->get_max_health();
        }

        if (spellslot == SlotId::W)
        {
            double damage = W->base_damage[level] + (0.025 * (1 * floor((src->get_total_ad() / 100)) * src->get_buff_count(0)));

            if (stage == 1)
                ret.physical = damage;
            
            if (stage == 2)
                ret.raw = damage;
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.6 * src->get_total_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = RDamage[level].first + 1.2 * src->get_bonus_ad() + RDamage[level].second * target->get_bonus_health();
        }

        return ret;
    }
};