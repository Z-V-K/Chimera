#pragma once
#include "../DamageChamp.h"

class Qiyana : public DamageChamp
{
public:
    Qiyana(GameObject* source) : DamageChamp(source) { }

    double Q1Damages[5] = { 50, 85, 120, 155, 190 };
    double Q2Damages[5] = { 128, 160, 192, 224, 256 };
    double RMonsterCap[3] = { 500, 750, 1000 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = Q1Damages[level] + .75 * src->get_bonus_ad();
            if (stage == 2)
                ret.physical = Q2Damages[level] + 1.44 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.5 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            double RDamage          = R->base_damage[level] + 1.7 * src->get_bonus_ad() + 0.1 * target->get_max_health();
            double RDamageMonsters = (RDamage > RMonsterCap[level]) ? RMonsterCap[level] : RDamage;

            ret.physical = target->is_jungle_minion() ? RDamageMonsters : RDamage;
        }

        return ret;
    }
};