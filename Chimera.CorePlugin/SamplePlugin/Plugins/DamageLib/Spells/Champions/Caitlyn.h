#pragma once
#include "../DamageChamp.h"

class Caitlyn : public DamageChamp
{
public:
	Caitlyn(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		1.25,
		1.45,
		1.65,
		1.85,
		2.05
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 2 * src->get_bonus_ad();
		}

		return ret;
	}
};