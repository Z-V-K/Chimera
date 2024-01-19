#pragma once
#include "../DamageChamp.h"

class Shyvana : public DamageChamp
{
public:
    Shyvana(GameObject* source) : DamageChamp(source)
    {
        Q->has_on_hit = true;
    }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        double WTickDamage[5] = {10, 16.25, 22.5, 28.75, 35};
        double EDamage[5] = { 60, 100, 140, 180, 220 };
        

        if (spellslot == SlotId::Q)
        {
            ret.physical = src->get_total_ad() + 0.35 * src->get_ap() + Q->base_damage[level] + 0.25 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = WTickDamage[level] + 0.15 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.magical = EDamage[level] + 0.4 * src->get_total_ad() + 0.9 * src->get_ap();

            if (stage == 2)
                ret.magical = EDamage[level] + 0.8 * src->get_total_ad() + 1.2 * src->get_ap() + (src->get_level() < 7 ? 75 : 75 + (src->get_level() - 6) * 5);
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 1.3 * src->get_ap();
        }

        return ret;
    }
};