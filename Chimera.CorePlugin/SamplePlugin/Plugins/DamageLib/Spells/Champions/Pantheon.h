#pragma once
#include "../DamageChamp.h"

class Pantheon : public DamageChamp
{
public:
    Pantheon(GameObject* source) : DamageChamp(source) { }

    double QDamage[5] = { 70, 100, 130, 160, 190 };
    double Q1Damage[18]
    {
        20.0,
        33.0,
        46.0,
        59.0,
        72.0,
        85.0,
        98.0,
        111.0,
        124.0,
        137.0,
        150.0,
        163.0,
        176.0,
        189.0,
        202.0,
        215.0,
        228.0,
        241.0
    };

    double EDamageExplosion[5] = { 55, 105, 155, 205, 255 };
    double RSpear[6] = { 40, 70, 100, 130, 160, 190 };
    double RShockwave[3] = { 300, 500, 700 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = QDamage[level] + 1.15 * src->get_bonus_ad();
            if (stage == 2)
                ret.physical = Q1Damage[std::min(src->get_level() - 1, 17)] + 1.15 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::W)
        {
            ret.physical = W->base_damage[0] + src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.physical = EDamageExplosion[level] + 1.5 * src->get_bonus_ad();

            if (stage == 2)
                ret.physical = 8.333333333 * src->get_total_ad();
        }

        if (spellslot == SlotId::R)
        {
            ret.physical = RSpear[src->get_spell(SlotId::Q)->get_level()] + 1.15 * src->get_bonus_ad();
            ret.magical  = RShockwave[level] + src->get_ap();
        }

        return ret;
    }
};