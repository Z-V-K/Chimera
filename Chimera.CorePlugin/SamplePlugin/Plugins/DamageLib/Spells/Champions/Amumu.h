#pragma once
#include "../DamageChamp.h"

class Amumu : public DamageChamp
{
public:
	Amumu(GameObject* source) : DamageChamp(source)
	{
	}

	double WDamagePercent[5] = {
		.01,
		1 / 80,
		.015,
		7 / 400,
		.02
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .85 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = 20 + (WDamagePercent[level] + .005 * src->get_ap() / 100) * target->get_max_health();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .5 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .8 * src->get_ap();
		}

		return ret;
	}
};