#pragma once
#include "../DamageChamp.h"

class Graves : public DamageChamp
{
public:
	Graves(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		45,
		60,
		75,
		90,
		105
	};

	double Q2Damage[5] = {
		85,
		120,
		155,
		190,
		225
	};

	double Q2DamagePercent[5] = {
		0.4,
		0.7,
		1.0,
		1.3,
		1.6
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + 0.800000011920929 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = Q2Damage[level] + Q2DamagePercent[level] * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 1.5 * src->get_bonus_ad();
		} 

		return ret;
	}
};