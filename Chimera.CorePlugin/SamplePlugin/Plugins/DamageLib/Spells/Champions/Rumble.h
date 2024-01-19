#pragma once
#include "../DamageChamp.h"

class Rumble : public DamageChamp
{
public:
    Rumble(GameObject* source) : DamageChamp(source) { }

    double Q1Damage[5]
    {
        180.0,
        220.0,
        260.0,
        300.0,
        340.0
    };

    double Q2Damage[5]
    {
        270.0,
        330.0,
        390.0,
        450.0,
        510.0
    };

    double E1Damage[5]
    {
        60.0,
        85.0,
        110.0,
        135.0,
        160.0
    };

    double E2Damage[5]
    {
		90.0,
        127.5,
        165.0,
        202.5,
        240.0
    };

    double R1Damage[5]
    {
        700.0,
        1050.0,
        1400.0
    };

    double R2Damage[5]
    {
        70.0,
        105.0,
        140.0
    };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.magical = Q1Damage[level] + 1.1 * src->get_ap();
            if (stage == 2)
                ret.magical = Q2Damage[level] + 1.65 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.magical = E1Damage[level] + .4 * src->get_ap();
            if (stage == 2)
                ret.magical = E2Damage[level] + .6 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = R1Damage[level] + 1.75 * src->get_ap();
            if (stage == 2)
                ret.magical = R2Damage[level] + .175 * src->get_ap();
        }

        return ret;
    }
};