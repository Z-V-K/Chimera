#pragma once
#include "../DamageChamp.h"

class Sivir : public DamageChamp
{
public:
    Sivir(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> QDamage[5] =
    {
        {15, 0.80},
        {30, 0.85},
        {45, 0.90},
        {60, 0.95},
        {75, 1.00},
    };

    const double WDamage[5] = { 30, 35, 40, 45, 50 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level].first + QDamage[level].second * src->get_total_ad() + 0.6 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = (target->is_minion() ? 0.65 : 1.0) * (WDamage[level] * src->get_total_ad());
        }

        return ret;
    }
};