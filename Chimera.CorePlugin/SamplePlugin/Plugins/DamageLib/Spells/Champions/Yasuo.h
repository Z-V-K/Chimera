#pragma once
#include "../DamageChamp.h"

class Yasuo : public DamageChamp
{
public:
	Yasuo(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1.05 * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.2 * src->get_bonus_ad() + 0.6 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 1.5 * src->get_bonus_ad();
		}

		return ret;
	}
};