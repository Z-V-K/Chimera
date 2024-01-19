#pragma once
#include "../DamageChamp.h"

class Vayne : public DamageChamp
{
public:
    Vayne(GameObject* source) : DamageChamp(source) { }

    const double QDamage[5] = { 0.75, 0.85, 0.95, 1.05, 1.15 };
    const double EDamage[5] = { 50, 85, 120, 155, 190 };
    const double EWall[5] = { 75, 127.5, 180, 232.5, 285 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = QDamage[level] * src->get_total_ad() + 0.5 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.physical = EDamage[level] + 0.5 * src->get_bonus_ad();

            if (stage == 2)
                ret.physical = EWall[level] + 0.75 * src->get_bonus_ad();
        }

        return ret;
    }
};