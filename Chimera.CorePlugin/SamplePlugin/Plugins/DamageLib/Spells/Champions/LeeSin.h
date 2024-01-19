#pragma once
#include "../DamageChamp.h"

class LeeSin : public DamageChamp
{
public:
	LeeSin(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		55,
		80,
		105,
		130,
		155
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + 1.1 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = Q1Damage[level] + 1.1 * src->get_bonus_ad() + .01 * (target->get_max_health() - target->get_health());
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 1 * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 2 * src->get_bonus_ad();
		}

		return ret;
	}
};