#pragma once
#include "../DamageChamp.h"

class Ashe : public DamageChamp
{
public:
	Ashe(GameObject* source) : DamageChamp(source)
	{

	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + 1 * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1 * src->get_ap();
		}

		return ret;
	}
};