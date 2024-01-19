#pragma once
#include "../DamageChamp.h"

class Draven : public DamageChamp
{
public:
	Draven(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		.7,
		.8,
		.9,
		1,
		1.1
	};

	double RDamagePercent[3] = {
		1.1,
		1.3,
		1.5
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] * src->get_bonus_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .5 * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + RDamagePercent[level] * src->get_bonus_ad();
		}

		return ret;
	}
};