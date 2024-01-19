#pragma once
#include "../DamageChamp.h"

class Taliyah : public DamageChamp
{
public:
    Taliyah(GameObject* source) : DamageChamp(source) { }

    const double QDamage[5] = { 45,65,85,105,125 };
    const double EDamage[5] = { 60, 105, 150, 195, 240 };
    const double EDetonation[5] = { 25, 45, 65, 85, 105 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            const double damage = QDamage[level] + 0.5 * src->get_ap();

            if (stage == 1)
                ret.magical = damage;

            if (stage == 2)
                ret.magical = 0.4 * damage;

            if (stage == 3)
                ret.magical = 1.9 * damage;
        }

        if (spellslot == SlotId::E)
        {
            const double campBonus = (target->is_jungle_minion() ? 1.5 : 1.0);

            if (stage == 1)
                ret.magical = campBonus * (EDamage[level] + 0.6 * src->get_ap());

            if (stage == 2)
                ret.magical = campBonus * (EDetonation[level] * 0.3 * src->get_ap());
        }

        return ret;
    }
};