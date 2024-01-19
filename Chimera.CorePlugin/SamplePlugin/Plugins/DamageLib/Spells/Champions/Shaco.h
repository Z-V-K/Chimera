#pragma once
#include "../DamageChamp.h"

class Shaco : public DamageChamp
{
public:
    Shaco(GameObject* source) : DamageChamp(source) { }

    double WMultiTarget[5]  = { 10, 15, 20, 25, 30 };
    double WSingleTarget[5] = { 25, 40, 55, 70, 85 };
    double WMonsterBonus[5] = { 10, 20, 30, 40, 50 };

    double EDamage[5] = { 70, 95, 120, 145, 170 };

    double RExplosion[3]        = { 150, 225, 300 };
    double RTickMultiTarget[3]  = { 10, 20, 30 };
    double RTickSingleTarget[3] = { 25, 50, 75 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            double damage = Q->base_damage[level] + 0.5 * src->get_bonus_ad();

            if (stage == 1)
                ret.physical = damage;

            if (stage == 2)
                ret.physical = damage + 20 + (15 / 17) * (src->get_level() - 1) + 0.25 * src->get_bonus_ad();
        }

        if (spellslot == SlotId::W)
        {
            if (stage == 1)
                ret.magical = WSingleTarget[level] + 0.18 * src->get_ap() + (target->is_jungle_minion() ? WMonsterBonus[level] : 0);

            if (stage == 2)
                ret.magical = WMultiTarget[level] + 0.12 * src->get_ap() + (target->is_jungle_minion() ? WMonsterBonus[level] : 0);
        }

        if (spellslot == SlotId::E)
        {
            double executeThreshold = target->get_health() / target->get_max_health();

            if (stage == 1)
                ret.magical = (executeThreshold < 0.3 ? 1.5 : 1.0) * (EDamage[level] + 0.8 * src->get_bonus_ad() + 0.6 * src->get_ap());

            if (stage == 2)
                ret.magical = (executeThreshold < 0.3 ? 1.5 : 1.0) * (EDamage[level] + 0.8 * src->get_bonus_ad() + 0.6 * src->get_ap() +
                              (15 + (35 / 17) * (src->get_level() - 1) + 0.1 * src->get_ap()));
        }

        if (spellslot == SlotId::R)
        {
            if (stage == 1)
                ret.magical = RExplosion[level] + 0.7 * src->get_ap();

            if (stage == 2)
                ret.magical = RTickSingleTarget[level] + 0.15 * src->get_ap();

            if (stage == 3)
                ret.magical = RTickMultiTarget[level] + 0.10 * src->get_ap();
        }

        return ret;
    }
};