#pragma once
#include "../DamageChamp.h"

class Ryze : public DamageChamp
{
public:
    Ryze(GameObject* source) : DamageChamp(source) { }

    double FluxBonus[4] = { 0.1, 0.4, 0.7, 1.0 };

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = (1 + FluxBonus[std::max(0, src->get_spell(SlotId::R)->get_level() - 1)]) * 
                           Q->base_damage[level] + 0.55 * src->get_ap() + 0.02 * src->get_bonus_mana();
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = W->base_damage[level] + 0.7 * src->get_ap() + 0.04 * src->get_bonus_mana();
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = E->base_damage[level] + 0.45 * src->get_ap() + 0.02 * src->get_bonus_mana();
        }

        return ret;
    }
};