#pragma once
#include "../DamageChamp.h"

class Teemo : public DamageChamp
{
public:
    Teemo(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const double ETick[5] = { 6, 12, 18, 24, 30 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.8 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            const double campBonus = target->is_jungle_minion() ? 1.5 : 1.0;
            ret.magical = campBonus * (ETick[level] + 0.1 * src->get_ap());
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.1375 * src->get_ap();
        }

        return ret;
    }
};