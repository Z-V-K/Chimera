#pragma once
#include "../DamageChamp.h"

class Talon : public DamageChamp
{
public:
    Talon(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const double WDamage[5] = { 40, 50, 60, 70, 80 };
        const double WReturn[5] = { 50, 80, 110, 140, 170 };

        if (spellslot == SlotId::Q)
        {
            const double damage = Q->base_damage[level] + src->get_bonus_ad();

            if (stage == 1)
                ret.physical = damage;

            if (stage == 2)
                ret.physical = 1.5 * damage;
        }

        if (spellslot == SlotId::W)
        {
            const double campBonus = target->is_jungle_minion() ? 1.05 : 1.0;

            if (stage == 1)
                ret.physical = campBonus * (WDamage[level] * 0.4 * src->get_bonus_ad());

            if (stage == 2)
                ret.physical = campBonus * (WReturn[level] * 0.8 * src->get_bonus_ad());
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] * src->get_bonus_ad();
        }

        return ret;
    }
};