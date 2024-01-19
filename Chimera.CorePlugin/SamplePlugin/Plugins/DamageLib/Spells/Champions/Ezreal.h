#pragma once
#include "../DamageChamp.h"

class Ezreal : public DamageChamp
{
public:
	Ezreal(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double WDamagePercent[5] = {
		0.7,
		0.75,
		0.8,
		0.85,
		0.9
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1.3 * src->get_total_ad() + .15 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .6 * src->get_bonus_ad() + WDamagePercent[level] * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .5 * src->get_bonus_ad() + .75 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1 * src->get_bonus_ad() + .9 * src->get_ap();
		}

		return ret;
	}
};