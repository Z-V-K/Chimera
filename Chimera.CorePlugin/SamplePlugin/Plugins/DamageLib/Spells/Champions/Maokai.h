#pragma once
#include "../DamageChamp.h"

class Maokai : public DamageChamp
{
public:
	Maokai(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		.02,
		.025,
		.03,
		.035,
		.04
	};

	double E1Damage[5] = {
		50,
		75,
		100,
		125,
		150
	};

	double E2Damage[5] = {
		110,
		160,
		210,
		260,
		310
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .4 * src->get_ap() + QDamagePercent[level] * src->get_max_health();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .4 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1Damage[level] + .25 * src->get_ap() + 0.059999998658895493 * src->get_bonus_health();
			if (stage == 2)
				ret.magical = E2Damage[level] + .8 * src->get_ap() + 0.11999999731779099 * src->get_bonus_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .75 * src->get_ap();
		}

		return ret;
	}
};