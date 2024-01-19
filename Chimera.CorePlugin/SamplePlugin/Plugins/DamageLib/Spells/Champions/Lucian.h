#pragma once
#include "../DamageChamp.h"

class Lucian : public DamageChamp
{
public:
	Lucian(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		.6,
		.75,
		.9,
		1.05,
		1.2
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .9 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .25 * src->get_bonus_ad() + .15 * src->get_ap();
		}

		return ret;
	}
};