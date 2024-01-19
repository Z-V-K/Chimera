#pragma once
#include "../DamageChamp.h"

class Ahri : public DamageChamp
{
public:

	Ahri(GameObject* source) : DamageChamp(source)
	{
		Q->has_stages = true;
		Q->stages = 2;

		W->has_stacks = true;
		W->stacks = 3;
	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1 || stage == 2)
				ret.magical = Q->base_damage[level] + .45 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .3 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] * .35 * src->get_ap();
		}

		return ret;
	}
};