#pragma once
#include "../DamageChamp.h"

class Vladimir : public DamageChamp
{
public:
    Vladimir(GameObject* source) : DamageChamp(source) { }

    const double QDamage[5] = { 80, 100, 120, 140, 160 };
    const double QEmpowered[5] = { 148, 185, 222, 259,296 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.magical = QDamage[level] + 0.6 * src->get_ap();

            if (stage == 2)
                ret.magical = QEmpowered[level] + 1.11 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.025 * src->get_bonus_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.015 * src->get_max_health() + 0.35 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.7 * src->get_ap();
        }

        return ret;
    }
};