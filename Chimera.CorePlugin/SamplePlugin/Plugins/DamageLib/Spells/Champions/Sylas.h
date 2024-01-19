#pragma once
#include "../DamageChamp.h"

class Sylas : public DamageChamp
{
public:
    Sylas(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        const double QDamage[5] = { 40, 60, 80, 100,120 };
        const double QExplosion[5] = { 70, 125, 180, 235, 290 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.magical = QDamage[level] + 0.4 * src->get_ap();

            if (stage == 2)
                ret.magical = QExplosion[level] + 0.9 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.9 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + src->get_ap();
        }

        if (spellslot == SlotId::R)
        {

        }

        return ret;
    }
};