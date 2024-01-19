#pragma once
#include "../DamageChamp.h"

class Ziggs : public DamageChamp
{
public:
	Ziggs(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.65 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 0.5 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.3 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 0.733333333 * src->get_ap();
		}

		return ret;
	}
};