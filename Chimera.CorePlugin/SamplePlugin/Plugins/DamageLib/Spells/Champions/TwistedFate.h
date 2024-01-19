#pragma once
#include "../DamageChamp.h"

class TwistedFate : public DamageChamp
{
public:
    TwistedFate(GameObject* source) : DamageChamp(source) { }

    const double WBlue[5] = { 40, 60, 80, 100, 120 };
    const double WRed[5] = { 30, 45 , 60, 75, 90 };
    const double WGold[5] = { 15, 22.5, 30, 37.5, 45 };
    const double EDamage[5] = { 65, 90, 115, 140, 165 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };
        
        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.8 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.magical = WBlue[level] + src->get_total_ad() + 1.15 * src->get_ap();

            if (stage == 2)
                ret.magical = WRed[level] + src->get_ap() + 0.7 * src->get_ap();

            if (stage == 3) 
                ret.magical = WGold[level] + src->get_ap() + 0.5 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = EDamage[level] + 0.5 * src->get_ap();
        }

        return ret;
    }
};