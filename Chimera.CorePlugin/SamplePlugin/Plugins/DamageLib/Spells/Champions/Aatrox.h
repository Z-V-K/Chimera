#pragma once
#include "../DamageChamp.h"

class Aatrox : public DamageChamp
{
public:
	Aatrox(GameObject* source) : DamageChamp(source)
	{
		Q->has_stages = true;
		Q->stages = 3;
	}

	std::pair<double, double> Q1Damage[5] = {
		{ 10, .6 },
		{ 30, .65 },
		{ 50, .7 },
		{ 70, .75 },
		{ 90, .8 }
	};

	std::pair<double, double> Q2Damage[5] = {
		{ 12.5, .75 },
		{ 37.5, .8125 },
		{ 62.5, .875 },
		{ 87.5, .9375 },
		{ 112.5, 1. }
	};

	std::pair<double, double> Q3Damage[5] = {
		{ 15, .9 },
		{ 45, .975 },
		{ 75, 1.05 },
		{ 105, 1.125 },
		{ 135, 1.2 }
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level].first + Q1Damage[level].second * src->get_total_ad();

			if (stage == 2)
				ret.physical = Q2Damage[level].first + Q2Damage[level].second * src->get_total_ad();

			if (stage == 3)
				ret.physical = Q3Damage[level].first + Q3Damage[level].second * src->get_total_ad();

			if (target->is_minion())
				ret.physical *= 0.44999998807907104;
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + .4 * src->get_total_ad();
		}

		return ret;
	}
};