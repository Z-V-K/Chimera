#pragma once
#include "../DamageChamp.h"

class Warwick : public DamageChamp
{
public:
	Warwick(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
		R->has_on_hit = true;
	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] * target->get_max_health() + 1.2 * src->get_bonus_ad() + src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 1.67 * src->get_bonus_ad();
		}

		return ret;
	}
};