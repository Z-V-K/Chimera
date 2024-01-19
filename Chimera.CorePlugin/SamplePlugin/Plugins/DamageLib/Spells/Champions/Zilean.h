#pragma once
#include "../DamageChamp.h"

class Zilean : public DamageChamp
{
public:
	Zilean(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.9 * src->get_ap();
		}

		return ret;
	}
};