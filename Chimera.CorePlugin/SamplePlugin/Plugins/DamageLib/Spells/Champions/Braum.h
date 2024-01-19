#pragma once
#include "../DamageChamp.h"

class Braum : public DamageChamp
{
public:
	Braum(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .025 * src->get_max_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .6 * src->get_ap();
		}

		return ret;
	}
};