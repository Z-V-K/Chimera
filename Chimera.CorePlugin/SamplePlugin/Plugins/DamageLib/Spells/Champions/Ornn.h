#pragma once
#include "../DamageChamp.h"

class Ornn : public DamageChamp
{
public:
    Ornn(GameObject* source) : DamageChamp(source) { }

    double WDamage[5] = { 2.4, 2.6, 2.8, 3, 3.2 };
    double WDamageMinionMinimum[5] = { 16, 26, 36, 46, 56 };
    double WDamageMonsterMinimum[5] = { 31, 36, 41, 46, 51 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.physical = Q->base_damage[level] + 1.1 * src->get_total_ad();
        }

        if (spellslot == SlotId::W)
        {
            double damage = WDamage[level] * target->get_max_health();

            if (target->is_hero())
            {
                ret.magical = damage;
            }

            if (target->is_minion())
            {
                ret.magical = (damage > WDamageMinionMinimum[level]) ? damage : WDamageMinionMinimum[level];
            }

            if (target->is_jungle_minion())
            {
                ret.magical = (damage > WDamageMonsterMinimum[level]) ? damage : WDamageMonsterMinimum[level];
            }
        }

        if (spellslot == SlotId::E)
        {
            ret.physical = E->base_damage[level] + 0.4 * (src->get_bonus_armor() + src->get_bonus_spell_block());
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.2 * src->get_ap();
        }

        return ret;
    }
};