#pragma once
#include "../DamageChamp.h"

class Gnar : public DamageChamp
{
public:
	Gnar(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		5,
		45,
		85,
		125,
		165
	};

	double Q2Damage[5] = {
		25,
		70,
		115,
		160,
		205
	};

	double W1Damage[5] = {
		0,
		10,
		20,
		30,
		40
	};

	double W1DamagePercent[5] = {
		0.06,
		0.08,
		0.1,
		0.12,
		0.14
	};

	double W2Damage[5] = {
		25,
		70,
		115,
		160,
		205
	};

	double E1Damage[5] = {
		50,
		85,
		120,
		155,
		190
	};

	double E2Damage[5] = {
		80,
		115,
		150,
		185,
		220
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + 1.15 * src->get_total_ad();
			if (stage == 2)
				ret.physical = Q2Damage[level] + 1.4 * src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
			{
				ret.magical = W1Damage[level] + W1DamagePercent[level] * target->get_max_health() + src->get_total_ad();
				if (target->is_minion() && target->is_neutral())
					ret.magical = std::min(300.0 + src->get_total_ad(), ret.magical);
			}

			if (stage == 2)
			{
				ret.physical = W2Damage[level] + 1.4 * src->get_total_ad();
			}
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.physical = E1Damage[level] + src->get_max_health() * .06;
			if (stage == 2)
				ret.physical = E2Damage[level] + src->get_max_health() * .06;
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .5 * src->get_bonus_ad() + 1 * src->get_ap();
		}

		return ret;
	}
};