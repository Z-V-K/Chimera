#pragma once
#include "../DamageChamp.h"

class Blitzcrank : public DamageChamp
{
public:
	Blitzcrank(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret = { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 1.2 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = target->get_max_health() * .01;

			if (target->is_minion())
				ret.magical += (60 + 7 * (src->get_level() - 1));
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = 1.75 * src->get_total_ad() + .25 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1.25 * src->get_ap();
		}

		return ret;
	}
};