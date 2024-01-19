#pragma once
#include "../DamageChamp.h"

class Alistar : public DamageChamp
{
public:
	Alistar(GameObject* source) : DamageChamp(source)
	{
		E->has_stages = true;
		E->stages = 2;
	}

	double E1BaseDamage[5]
	{
		80,
		110,
		140,
		170,
		200
	};

	double E2BaseDamage[5]
	{
		8,
		11,
		14,
		17,
		20
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 1 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1BaseDamage[level] + .4 * src->get_ap();

			if (stage == 2)
				ret.magical = E2BaseDamage[level] + .04 * src->get_ap();
		}

		return ret;
	}
};