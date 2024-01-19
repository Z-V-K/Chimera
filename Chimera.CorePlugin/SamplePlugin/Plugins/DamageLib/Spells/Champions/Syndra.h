#pragma once
#include "../DamageChamp.h"

class Syndra : public DamageChamp
{
public:
    Syndra(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            const double damage = W->base_damage[level] + 0.7 * src->get_ap();
            ret.magical = damage;

            if (src->get_buff_count(0) >= 60)
            {
                double apMod = floor(src->get_ap() / 100);
                ret.raw = (0.12 + apMod * 0.02) * damage;
            }
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.45 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.17 * src->get_ap();
        }

        return ret;
    }
};