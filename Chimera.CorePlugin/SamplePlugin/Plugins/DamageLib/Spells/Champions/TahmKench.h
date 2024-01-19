#pragma once
#include "../DamageChamp.h"

class TahmKench : public DamageChamp
{
public:
    TahmKench(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            const double passive = 8 + (52 / 17) * (src->get_level() - 1);
            const double healthBonus = (0.02 * floor(src->get_bonus_health() / 100)) * src->get_ap();
            ret.magical = Q->base_damage[level] + src->get_ap() + passive + healthBonus + 0.03 * src->get_bonus_health();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 1.5 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + (0.15 + (0.07 * floor(src->get_ap() / 100))) * target->get_max_health();
        }

        return ret;
    }
};