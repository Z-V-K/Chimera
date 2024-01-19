#pragma once
#include "../DamageChamp.h"

class Renekton : public DamageChamp
{
public:
    Renekton(GameObject* source) : DamageChamp(source)
    {
        W->has_on_hit = true;
    }

    double Q1Damage[5]
    {
        60.0,
        90.0,
        120.0,
        150.0,
        180.0
    };

    double Q2Damage[5]
    {
        90.0,
        135.0,
        180.0,
        225.0,
        270.0
    };

    double W1Damage[5]
    {
        10,
        40,
        70,
        110,
        130
    };

    double W2Damage[5]
    {
        15,
        60,
        105,
        150,
        195
    };

    double ESlice[5] = { 40, 70, 100, 130, 160 };
    double EDice[5] = { 70, 115, 160, 205, 250 };
    double EDiceBonus[5] = { 30, 45, 60, 75, 90 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = Q1Damage[level] + src->get_bonus_ad();
            if (stage == 2)
                ret.physical = Q2Damage[level] + 1.4 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.physical = W1Damage[level] + .75 * src->get_total_ad() + 2 * src->get_total_ad();

            if (stage == 2)
                ret.physical = W2Damage[level] + .75 * src->get_total_ad() + 3 * src->get_total_ad();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1) // slice
                ret.physical = ESlice[level] + 0.9 * src->get_bonus_ad();

            if (stage == 2) // dice
                ret.physical = EDice[level] + 1.35 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.05 * (src->get_bonus_ad() + src->get_ap());
        }

        return ret;
    }
};