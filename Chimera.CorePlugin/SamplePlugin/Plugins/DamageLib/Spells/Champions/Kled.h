#pragma once
#include "../DamageChamp.h"

class Kled : public DamageChamp
{
public:
	Kled(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		30,
		55,
		80,
		105,
		130
	};

	double Q2Damage[5] =
	{
		60,
		110,
		160,
		210,
		260
	};

	double Q3Damage[5] = {
		35,
		50,
		65,
		80,
		95
	};

	double WDamagePercent[5] = {
		0.045,
		0.05,
		0.055,
		0.06,
		0.065
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + .65 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = Q2Damage[level] + 1.3 * src->get_bonus_ad();
			if (stage == 3)
				ret.physical = Q3Damage[level] + .8 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + (WDamagePercent[level] + .05 * src->get_bonus_ad() / 100) * target->get_max_health();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .65 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] * target->get_max_health();
		}

		return ret;
	}
};