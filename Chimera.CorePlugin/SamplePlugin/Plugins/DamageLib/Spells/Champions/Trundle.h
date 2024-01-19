#pragma once
#include "../DamageChamp.h"

class Trundle : public DamageChamp
{
public:
    Trundle(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> QDamage[5] =
    {
        {20, 0.15},
        {40, 0.25},
        {60, 0.35},
        {80, 0.45},
        {100, 0.55}
    };

    const double RDamage[3] = { 20, 25, 30 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level].first * QDamage[level].second * src->get_total_ad();
        }

        if (spellslot == SlotId::R)
        {
            const double damage = RDamage[level] + (0.02 * floor(src->get_ap() / 100)) * target->get_max_health();

            if (stage == 1)
                ret.magical = 0.5 * damage;

            if (stage == 2)
                ret.magical = 0.125 * damage;
        }

        return ret;
    }
};