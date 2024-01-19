#pragma once
#include "../DamageChamp.h"

class Karthus : public DamageChamp
{
public:
	Karthus(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.34999999403953552 * src->get_ap();
			if (target->is_minion() && target->is_neutral())
				ret.magical *= 0.85000002384185791;
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .2 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .75 * src->get_ap();
		}

		return ret;
	}
};