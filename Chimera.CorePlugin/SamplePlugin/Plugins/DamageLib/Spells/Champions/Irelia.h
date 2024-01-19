#pragma once
#include "../DamageChamp.h"

class Irelia : public DamageChamp
{
public:
	Irelia(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .6 * src->get_total_ad();
			if (target->is_minion())
				ret.physical += 43 + 12 * src->get_level();
		}

		if (spellslot == SlotId::W )
		{
			ret.physical = W->base_damage[level] + 1.2 * src->get_total_ad() + 1.2 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .7 * src->get_ap();
		}


		return ret;
	}
};