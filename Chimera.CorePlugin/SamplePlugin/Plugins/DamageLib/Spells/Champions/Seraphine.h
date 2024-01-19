#pragma once
#include "../DamageChamp.h"

class Seraphine : public DamageChamp
{
public:
    Seraphine(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QDamage[5] = {
        {  55, 0.45},
        {  70, 0.50},
        {  85, 0.55},
        { 100, 0.60},
        { 115, 0.65}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            double missingHealth = floor(((1 - (src->get_health() / src->get_max_health())) / 0.075)) * 0.05;
            ret.magical = (1 + missingHealth) * (QDamage[level].first + QDamage[level].second * src->get_ap());
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.35 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.6 * src->get_ap();
        }

        return ret;
    }
};