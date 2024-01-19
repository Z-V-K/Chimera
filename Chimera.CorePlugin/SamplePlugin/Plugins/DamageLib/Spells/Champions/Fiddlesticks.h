#pragma once
#include "../DamageChamp.h"

class Fiddlesticks : public DamageChamp
{
public:
	Fiddlesticks(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		0.06,
		0.07,
		0.08,
		0.09,
		0.1
	};

	double Q2Damage[5] = {
		0.12,
		0.14,
		0.16,
		0.18,
		0.2
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = (Q1Damage[level] + .02 * src->get_ap() / 100) * target->get_health();
			if (stage == 2)
				ret.magical = (Q2Damage[level] + .04 * src->get_ap() / 100) * target->get_health();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 7 / 80 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .5 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 9 / 80 * src->get_ap() * 20;
		}

		return ret;
	}
};