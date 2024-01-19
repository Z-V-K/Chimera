#pragma once
#include "../DamageChamp.h"

class Kindred : public DamageChamp
{
public:
	Kindred(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .75 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + .2 * src->get_bonus_ad() + .2 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .8 * src->get_bonus_ad();
		}

		return ret;
	}
};