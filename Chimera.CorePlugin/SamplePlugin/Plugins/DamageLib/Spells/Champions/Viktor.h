#pragma once
#include "../DamageChamp.h"

class Viktor : public DamageChamp
{
public:
    Viktor(GameObject* source) : DamageChamp(source) { }

    const double QDamage[5] = { 60, 75, 90, 105, 120 };
    const double QEmpoweredAA[5] = { 20, 45, 70, 95, 120 };
    const double EDamage[5] = { 70, 110, 150, 190, 230 };
    const double EExplosion[5] = { 20, 50, 80, 110, 140 };
    const double RDamage[3] = { 100, 175, 250 };
    const double RTick[3] = { 65, 105, 145 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = QDamage[level] + 0.4 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            if (stage == 1)
                ret.magical = EDamage[level] + 0.5 * src->get_ap();

            if (stage == 2)
                ret.magical = EExplosion[level] + 0.8 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RDamage[level] + 0.5 * src->get_ap();

            if (stage == 2)
                ret.magical = RTick[level] + 0.45 * src->get_ap();
        }

        return ret;
    }
};