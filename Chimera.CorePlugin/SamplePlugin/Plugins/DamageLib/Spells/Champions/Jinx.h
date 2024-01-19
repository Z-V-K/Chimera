#pragma once
#include "../DamageChamp.h"

class Jinx : public DamageChamp
{
public:
	Jinx(GameObject* source) : DamageChamp(source) { }

	double RDamagePercent[3] = {
		.25,
		.3,
		.35
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = .1 * src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + 1.6 * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 1 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + RDamagePercent[level] * (target->get_max_health() - target->get_health()) + .15 * src->get_bonus_ad();
		}

		return ret;
	}
};