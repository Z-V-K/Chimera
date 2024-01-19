#pragma once
#include "../DamageChamp.h"

class Veigar : public DamageChamp
{
public:
    Veigar(GameObject* source) : DamageChamp(source) { }

    const std::pair<double, double> QDamage[5] =
    {
        {80, 0.45},
        {120, 0.5},
        {160, 0.55 },
        {200, 0.6},
        {240, 0.65}
    };

    const std::pair<double, double> WDamage[5] =
    {
        {85,  0.8},
        {140, 0.8},
        {195, 0.9 },
        {250, 1.0},
        {305, 1.1}
    };

    const std::pair<double, double> RDamage[3] =
    {
        {175, 0.65},
        {250, 0.70},
        {324, 0.75}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = QDamage[level].first + QDamage[level].second * src->get_ap();
        }


        if (spellslot == SlotId::W)
        {
            ret.magical = WDamage[level].first + WDamage[level].second * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            const double missingHealth = (1 - (target->get_health() / target->get_max_health())) * 100;
            const double amp = 1.0 + (missingHealth >= 0.6666 ? 1.0 : missingHealth * 0.015);

            ret.magical = amp * (RDamage[level].first + RDamage[level].second * src->get_ap());
        }

        return ret;
    }
};