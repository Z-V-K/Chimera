#pragma once
#include "../DamageChamp.h"

class Gragas : public DamageChamp
{
public:
	Gragas(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .8 * src->get_ap();
			if (target->is_minion())
				ret.magical *= 0.7;
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .7 * src->get_ap() + .07 * target->get_max_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .8 * src->get_ap();
		}

		return ret;
	}
};