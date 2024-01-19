#pragma once
#include "../DamageChamp.h"

class Kaisa : public DamageChamp
{
public:
	Kaisa(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .4 * src->get_bonus_ad() + .3 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 1.3 * src->get_total_ad() + .45 * src->get_ap();
		}

		return ret;
	}
};