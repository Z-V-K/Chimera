#pragma once
#include "../DamageChamp.h"

class Gangplank : public DamageChamp
{
public:
	Gangplank(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double R1Damage[3] = {
		40,
		70,
		100
	};

	double R2Damage[3] = {
		480,
		840,
		1200
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1 * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + .1 * src->get_ap();
			if (stage == 2)
				ret.magical = R2Damage[level] + 1.2 * src->get_ap();
		}

		return ret;
	}
};