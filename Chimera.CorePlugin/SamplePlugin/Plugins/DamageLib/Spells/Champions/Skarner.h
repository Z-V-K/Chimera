#pragma once
#include "../DamageChamp.h"

class Skarner : public DamageChamp
{
public:
    Skarner(GameObject* source) : DamageChamp(source) { }

    const double QDamage[5] = { 0.01, 0.015, 0.02, 0.025, 0.03 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = QDamage[level] * (double)target->get_max_health() + 0.2 * (double)src->get_total_ad();
            if (stage == 2)
                ret.physical = QDamage[level] * (double)target->get_max_health() + 0.2 * (double)src->get_total_ad() + 0.3 * (double)src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.2 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.5 * src->get_ap();
        }

        return ret;
    }
};