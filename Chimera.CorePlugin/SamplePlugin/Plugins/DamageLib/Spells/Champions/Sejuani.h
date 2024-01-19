#pragma once
#include "../DamageChamp.h"

class Sejuani : public DamageChamp
{
public:
    Sejuani(GameObject* source) : DamageChamp(source) { }

    double WDamage[5]             = { 20, 25, 30, 35, 40 };
    double WDamageReProcc[5]      = { 30, 70, 110, 150, 190 };
    double RDamage[3]             = { 125,150,175 };
    double RDamageMoreDistance[3] = { 200, 300, 400 };
    double RDamageExplosion[3]    = { 200, 300, 400 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] + 0.6 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.physical = WDamage[level] + 0.2 * src->get_ap() + 0.02 * src->get_max_health();
            
            if (stage == 2)
                ret.physical = WDamageReProcc[level] + 0.6 * src->get_ap() + 0.06 * src->get_max_health();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.6 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RDamage[level] + 0.4 * src->get_ap();

            if (stage == 2)
                ret.magical = RDamageMoreDistance[level] + 0.8 * src->get_ap();

            if (stage == 3)
                ret.magical = RDamageExplosion[level] + 0.8 * src->get_ap();
        }

        return ret;
    }
};