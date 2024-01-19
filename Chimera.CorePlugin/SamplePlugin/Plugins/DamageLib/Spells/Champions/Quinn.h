#pragma once
#include "../DamageChamp.h"

class Quinn : public DamageChamp
{
public:
    Quinn(GameObject* source) : DamageChamp(source) { }

    std::pair<double, double> QDamage[5] = {
        {  20, 0.8},
        {  45, 0.9},
        {  70, 1.0},
        {  95, 1.1},
        { 120, 1.2}
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level].first + QDamage[level].second * src->get_total_ad() + 0.5 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.2 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = 0.7 * src->get_total_ad();
        }

        return ret;
    }
};