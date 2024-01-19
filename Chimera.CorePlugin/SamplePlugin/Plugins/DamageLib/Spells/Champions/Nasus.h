#pragma once
#include "../DamageChamp.h"

class Nasus : public DamageChamp
{
public:
	Nasus(GameObject* source) : DamageChamp(source)
	{
	}

	std::pair<double, double> ETickDamage[5] = {
		{11, .12},
		{19, .12},
		{27, .12},
		{35, .12},
		{43, .12}
	};

	std::pair<double, double> RTickDamage[3] = {
		{.015, 0.05},
		{.02,  0.05},
		{.025, 0.05},
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + src->get_buff_count(0x1b1d7345);
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E->base_damage[level] + .6 * src->get_ap();

			if (stage == 2)
				ret.magical = ETickDamage[level].first + ETickDamage[level].second * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			int apMult = std::floor(src->get_ap() / 100);
			ret.magical = (RTickDamage[level].first + apMult) * target->get_max_health();
		}

		return ret;
	}
};