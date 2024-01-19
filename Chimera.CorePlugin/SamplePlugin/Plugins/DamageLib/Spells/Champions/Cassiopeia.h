#pragma once
#include "../DamageChamp.h"

class Cassiopeia : public DamageChamp
{
public:
	Cassiopeia(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .9 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .15 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = (48 + 4 * src->get_level()) + .1 * src->get_ap();
			if (target->has_buff_type(BuffType::Poison))
				ret.magical += E->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .5 * src->get_ap();
		}

		return ret;
	}
};