#pragma once
#include "../DamageChamp.h"

class Lux : public DamageChamp
{
public:
	Lux(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1 * src->get_ap();
		}

		return ret;
	}
};