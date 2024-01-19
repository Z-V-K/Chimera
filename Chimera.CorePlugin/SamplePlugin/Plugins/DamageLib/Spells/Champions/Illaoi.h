#pragma once
#include "../DamageChamp.h"

class Illaoi : public DamageChamp
{
public:
	Illaoi(GameObject* source) : DamageChamp(source) { }

	double WDamage[5] = {
		.03,
		.035,
		.04,
		.045,
		.05
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = (10 * src->get_level()) + 1.2 * src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = (WDamage[level] + .04 * src->get_total_ad() / 100) * target->get_max_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .5 * src->get_bonus_ad();
		}

		return ret;
	}
};