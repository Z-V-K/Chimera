#pragma once
#include "../DamageChamp.h"

class MissFortune : public DamageChamp
{
public:
	MissFortune(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double Q1Damage[5] = {
		20,
		45,
		70,
		95,
		120
	};

	double Q2Damage[5] = {
		40,
		90,
		140,
		190,
		240
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + src->get_total_ad() + .35 * src->get_ap();
			if (stage == 2)
				ret.physical = Q2Damage[level] + 2 * src->get_total_ad() + .7 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 1.2000000476837158 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = .75 * src->get_total_ad() + .25 * src->get_ap();
		}

		return ret;
	}
};