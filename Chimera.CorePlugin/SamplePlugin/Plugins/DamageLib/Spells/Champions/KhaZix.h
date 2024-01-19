#pragma once
#include "../DamageChamp.h"

class KhaZix	 : public DamageChamp
{
public:
	KhaZix	(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		70,
		95,
		120,
		145,
		170
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + 1.15 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = (Q1Damage[level] + 1.1499999761581421 * src->get_bonus_ad()) * 1.1000000238418579;
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + 1 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .2 * src->get_bonus_ad();
		}

		return ret;
	}
};