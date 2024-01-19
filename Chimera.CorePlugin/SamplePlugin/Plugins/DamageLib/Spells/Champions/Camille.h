#pragma once
#include "../DamageChamp.h"

class Camille : public DamageChamp
{
public:
	Camille(GameObject* source) : DamageChamp(source)
	{
		Q->has_stages = true;
		Q->stages = 3;

		W->has_stages = true;
		W->stages = 2;
	}

	double Q1Damage[5] = {
		.2,
		.25,
		.3,
		.35,
		.5
	};

	double Q2Damage[5] = {
		.4,
		.5,
		.6,
		.7,
		.8
	};

	double W1Damage[5] = {
		70,
		100,
		130,
		160,
		190
	};

	double W2Damage[5] = {
		.05,
		.055,
		.06,
		.065,
		.07
	};

	double RDamagePercent[3] = {
		.04,
		.06,
		.08
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] * src->get_total_ad();
			if (stage == 2)
				ret.physical = Q1Damage[level] * src->get_total_ad();
			if (stage == 3)
			{
				ret.physical = Q2Damage[level] * src->get_total_ad();
				ret.raw = (40 + 4 * src->get_level()) * ret.physical;

				ret.physical -= ret.raw;
			}
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.physical = W1Damage[level] + .6 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = W2Damage[level] + .025 * src->get_bonus_ad() / 100 * target->get_max_health();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .9 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + RDamagePercent[level] * target->get_health();
		}

		return ret;
	}
};