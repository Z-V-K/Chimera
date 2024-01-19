#pragma once
#include "../DamageChamp.h"

class Brand : public DamageChamp
{
public:
	Brand(GameObject* source) : DamageChamp(source) { }

	const uint32_t hashAblaze = 0x5242823b;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret = { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .55 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .6 * src->get_ap();

			if (target->has_buff(hashAblaze))
				ret.magical += ret.magical * .25;
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .45 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .25 * src->get_ap();
		}

		return ret;
	}
};