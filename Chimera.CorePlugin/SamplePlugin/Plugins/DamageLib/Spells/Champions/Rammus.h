#pragma once
#include "../DamageChamp.h"

class Rammus : public DamageChamp
{
public:
    Rammus(GameObject* source) : DamageChamp(source) { }

    double RDamage[3]       = { 150, 175, 250 };
    double RDamageWave[3]   = { 20, 30, 40 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = 15 + 0.15 * src->get_armor();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RDamage[level] + 0.6 * src->get_ap();

            if (stage == 2)
                ret.magical = RDamageWave[level] + 0.10 * src->get_total_ad();
        }

        return ret;
    }
};