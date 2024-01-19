#pragma once
#include "../DamageChamp.h"

class Nunu : public DamageChamp
{
public:
    Nunu(GameObject* source) : DamageChamp(source) { }

    double QDamage[5] = { 60, 100, 140, 180, 220 };
    double QDamageNonChampion[5] = { 400, 600, 800, 1000, 1200 };
    double WDamage[5] = { 36, 45, 54, 64, 72 };
    double EDamagePerSnowball[5] = {16, 24, 32, 40, 48};
    double RBaseDamage[3] = { 625, 950, 1275 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            if (src->is_hero())
            {
                ret.magical = QDamage[level] + 0.65 * src->get_ap() + 0.05 * src->get_bonus_health();
            }
            else {
                ret.raw = QDamageNonChampion[level];
            }            
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = WDamage[level] + 0.3 * src->get_ap();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = EDamagePerSnowball[level] + 0.1 * src->get_ap();
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = RBaseDamage[level] + 3 * src->get_ap();
        }

        return ret;
    }
};