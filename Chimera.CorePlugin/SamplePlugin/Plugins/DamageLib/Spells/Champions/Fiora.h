#pragma once
#include "../DamageChamp.h"

class Fiora : public DamageChamp
{
public:
	Fiora(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double QDamagePercent[5] = {
		0.9,
		0.95,
		1.0,
		1.05,
		1.1
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 1 * src->get_ap();
		}

		return ret;
	}
};