#pragma once
#include "../DamageChamp.h"

class Swain : public DamageChamp
{
public:
    Swain(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const double QDamage[5] = { 65, 85, 105, 125, 145 };
        const double QBolt[5] = { 15, 25, 35, 45, 55 };
        const double EDamage[5] = { 30, 70, 105, 140, 175 };
        const double EDetonation[5] = { 35, 45, 55, 65, 75 };
        const double RDamage[3] = { 150,225, 300 };
        const double RTick[3] = { 20, 40, 60 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.magical = QDamage[level] + 0.4 * src->get_ap();

            if (stage == 2)
                ret.magical = QBolt[level] + 0.1 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.55 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.magical = EDamage[level] + 0.25 * src->get_ap();

            if (stage == 2)
                ret.magical = EDetonation[level] + 0.25 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RDamage[level] + 0.6 * src->get_ap();

            if (stage == 2)
                ret.magical = RTick[level] + 0.1 * src->get_ap();
        }

        return ret;
    }
};