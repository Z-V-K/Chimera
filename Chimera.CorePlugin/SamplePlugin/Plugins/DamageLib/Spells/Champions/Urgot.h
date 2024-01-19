#pragma once
#include "../DamageChamp.h"

class Urgot : public DamageChamp
{
public:
    Urgot(GameObject* source) : DamageChamp(source) { }

    const double WDamage[5] = { 0.2, 0.235, 0.27, 0.305, 0.34 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 0.7 * src->get_total_ad();
        }

        if (spellslot == SlotId::W)
        {
            const double damage = 20 + WDamage[level] * src->get_total_ad();
            ret.physical = damage;

            if (target->is_jungle_minion() || target->is_minion())
                ret.physical = damage < 50 ? 50 : damage;
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = R->base_damage[level] + 0.5 * src->get_bonus_ad();
        }

        return ret;
    }
};