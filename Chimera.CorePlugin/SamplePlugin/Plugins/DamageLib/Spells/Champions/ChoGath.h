#pragma once
#include "../DamageChamp.h"

class ChoGath : public DamageChamp
{
public:

	ChoGath(GameObject* source) : DamageChamp(source) { }

	const uint32_t hashFeast = 0x8682fc00;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 1 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .3 * src->get_ap() + (src->get_buff_count(hashFeast) * .005 + .03) * target->get_max_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.raw = R->base_damage[level] + .5 * src->get_ap() + .1 * src->get_bonus_health();

			if (target->is_minion())
				ret.raw = 1200 + .5 * src->get_ap() + .1 * src->get_bonus_health();
		}

		return ret;
	}
};