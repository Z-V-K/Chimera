#pragma once
#include "../DamageChamp.h"

class Vex : public DamageChamp
{
public:
    Vex(GameObject* source) : DamageChamp(source) { }

    const double RDamage[3] = { 75, 125, 175 };
    const double RRecast[3] = { 150, 250, 350 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.7 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.3 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.3 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RDamage[level] + 0.2 * src->get_ap();

            if (stage == 2)
                ret.magical = RRecast[level] + 0.5 * src->get_ap();
        }

        return ret;
    }
};