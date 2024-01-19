#pragma once
#include "../DamageChamp.h"

class Pyke : public DamageChamp
{
public:
    Pyke(GameObject* source) : DamageChamp(source) { }

    double RExecuteHeatlh[13] = { 250, 290, 330,  370, 400, 430, 450, 470, 490, 510, 530, 540, 550 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 0.6 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::E)
        {
            if (target->is_hero())
                ret.physical = E->base_damage[level] + src->get_bonus_ad();
        }

        if (spellslot == SlotId::R)
        {
            double executeThreshold = RExecuteHeatlh[level] + 0.8 * src->get_bonus_ad() + (1.5 * src->get_lethality());
            
            if (target->get_health() < executeThreshold)
                ret.raw = executeThreshold;
            else
                ret.physical = 0.5 * executeThreshold;
        }

        return ret;
    }
};