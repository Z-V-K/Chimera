#pragma once
#include "../DamageChamp.h"

class Rell : public DamageChamp
{
public:
    Rell(GameObject* source) : DamageChamp(source) { }

    DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
    {
        DamageOutput ret{ 0, 0, 0 };

        if (spellslot == SlotId::Q)
        {
            ret.magical = (target->is_jungle_minion() ? 3.0 : 1.0) * (Q->base_damage[level] + 0.6 * src->get_ap());
        }

        if (spellslot == SlotId::W)
        {
            ret.magical = (target->is_jungle_minion() ? 3.0 : 1.0) * (W->base_damage[level] + 0.4 * src->get_ap());
        }

        if (spellslot == SlotId::E)
        {
            ret.magical = (target->is_jungle_minion() ? 2.5 : 1.0) * (E->base_damage[level] + 0.5 * src->get_ap() + 0.4 * src->get_max_health());
        }

        if (spellslot == SlotId::R)
        {
            ret.magical = R->base_damage[level] + 0.1375 * src->get_ap();
        }

        return ret;
    }
};