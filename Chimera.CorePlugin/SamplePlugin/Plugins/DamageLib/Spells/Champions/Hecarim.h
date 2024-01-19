#pragma once
#include "../DamageChamp.h"

class Hecarim : public DamageChamp
{
public:
	Hecarim(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .9 * src->get_bonus_ad();
			if (target->is_minion())
				ret.physical *= .6;
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .2 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .5 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1 * src->get_ap();
		}

		return ret;
	}
};