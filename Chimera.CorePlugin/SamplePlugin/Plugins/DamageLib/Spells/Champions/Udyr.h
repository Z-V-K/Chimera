#pragma once
#include "../DamageChamp.h"

class Udyr : public DamageChamp
{
public:
    Udyr(GameObject* source) : DamageChamp(source) { }

    const double QDamage[6] = { 3, 4, 5, 6, 7, 8 };
    const double QBonus[6] = { 5, 11, 17, 23, 29, 35 };
    const double RTick[6] = { 10, 19, 28, 37, 46,55 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (stage == 1)
                ret.physical = (QDamage[level] + 0.04 * floor(src->get_bonus_ad() / 100)) * target->get_max_health();

            if (stage == 2)
                ret.physical = QBonus[level] + 0.25 * src->get_bonus_ad();

            if (stage == 3)
            {
                ret.physical = (0.02 + (0.02 / 17) * (src->get_level() - 1) + 0.02 * floor(src->get_bonus_ad() / 100)) * target->get_max_health();

                const double lightning = (0.015 + (0.015 / 17) * (src->get_level() - 1) + 0.08 * floor(src->get_ap() / 100)) * target->get_max_health();

                ret.magical = lightning;

                if (target->is_minion())
                {
                    const double minionDamage = 40 + (120 / 17) * (src->get_level() - 1);
                    ret.magical = lightning < minionDamage ? minionDamage : lightning;
                }

                if (target->is_jungle_minion())
                {
                    const double monsterDamage = 20 + src->get_bonus_ad() + 0.5 * src->get_ap();
                    ret.magical = lightning > monsterDamage ? monsterDamage : lightning;
                }
                    
            }
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RTick[level] + 0.175 * src->get_ap();

            if (stage == 2)
            {
                const double tick = (0.01 + (0.01 / 17) * (src->get_level() - 1) + (0.004375 * floor(src->get_ap() / 100))) * target->get_max_health();
                const double monsterCap = 10 + (40 / 17) + (src->get_level() - 1);
                
                ret.magical = tick;

                if (target->is_jungle_minion())
                    ret.magical = tick > monsterCap ? monsterCap : tick;
            }
        }

        return ret;
    }
};