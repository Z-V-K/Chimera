#pragma once
#include "../DamageChamp.h"

class Elise : public DamageChamp
{
public:
	Elise(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double Q1Damage[5] = {
		40,
		75,
		110,
		145,
		180
	};

	double Q2Damage[5] = {
		60,
		90,
		120,
		150,
		180
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = Q1Damage[level] + (.04 * .0003 * src->get_ap()) * target->get_health();
			if (stage == 2)
				ret.magical = Q2Damage[level] + (.08 * .0003 * src->get_ap()) * (target->get_max_health() - target->get_health());
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .95 * src->get_ap();
		}


		return ret;
	}
};