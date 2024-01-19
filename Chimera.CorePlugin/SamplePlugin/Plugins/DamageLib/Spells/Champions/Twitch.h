#pragma once
#include "../DamageChamp.h"

class Twitch : public DamageChamp
{
public:
    Twitch(GameObject* source) : DamageChamp(source) { }

    const double EDamage[5] = { 20,30,40,50,60 };
    const double ETick[5] = { 15, 20, 25, 30, 35 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.physical = EDamage[level];

            if (stage == 2)
                ret.physical = stacks * (ETick[level] + 0.35 * src->get_bonus_ad() + 0.3 * src->get_ap());
        }

        return ret;
    }
};