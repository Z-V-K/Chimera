#pragma once
#include "../DamageChamp.h"

class Viego : public DamageChamp
{
public:
    Viego(GameObject* source) : DamageChamp(source)
    {
        R->has_on_hit = true;
    }

    const double QDamage[5] = {15, 30, 45, 60, 75};
    const double RDamage[3] = { 12, 16, 20 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = (1 + src->get_crit()) * (QDamage[level] + 0.7 * src->get_total_ad()) + (target->is_jungle_minion() ? 20 : 0);
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = (RDamage[level] + (0.05 * floor(src->get_bonus_ad() / 100))) * (target->get_max_health() - target->get_health());
        }

        return ret;
    }
};