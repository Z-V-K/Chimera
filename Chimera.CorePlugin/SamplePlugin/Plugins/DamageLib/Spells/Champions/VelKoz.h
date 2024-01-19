#pragma once
#include "../DamageChamp.h"

class VelKoz : public DamageChamp
{
public:
    VelKoz(GameObject* source) : DamageChamp(source) { }

    const double WDamage[5] = { 30, 50, 70, 90, 110 };
    const double WDetonate[5] = { 45, 75, 105, 135, 165 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = Q->base_damage[level] * 0.9 * src->get_ap();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.magical = WDamage[level] + 0.2 * src->get_ap();

            if (stage == 2)
                ret.magical = WDetonate[level] + 0.25 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.3 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.0962 * src->get_ap();
        }

        return ret;
    }
};