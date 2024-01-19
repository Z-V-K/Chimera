#pragma once
#include "../DamageChamp.h"

class Corki : public DamageChamp
{
public:
	Corki(GameObject* source) : DamageChamp(source)
	{
	}

	double W1Damage[5] = {
		150,
		225,
		300,
		375,
		450
	};

	double W2Damage[18] = {
		150.0,
		150.0,
		150.0,
		150.0,
		150.0,
		150.0,
		150.0,
		175.0,
		200.0,
		225.0,
		250.0,
		275.0,
		300.0,
		325.0,
		350.0,
		400.0,
		450.0,
		500.0
	};

	double R1Damage[3] = {
		80,
		115,
		150
	};

	double R1DamagePercent[3] = {
		.15,
		.45,
		.75
	};

	double R2Damage[3] = {
		160,
		230,
		300
	};

	double R2DamagePercent[3] = {
		.3,
		.9,
		1.5
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .7 * src->get_bonus_ad() + .5 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = W1Damage[level] + .1 * src->get_ap();

			if (stage == 2)
				ret.magical = W2Damage[std::min((int)src->get_level() - 1, 17)] + 10 * src->get_bonus_ad() + 1.2 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .15 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + R1DamagePercent[level] * src->get_total_ad() + .12 * src->get_ap();
			if (stage == 2)
				ret.magical = R2Damage[level] + R2DamagePercent[level] * src->get_total_ad() + .24 * src->get_ap();
		}

		return ret;
	}
};