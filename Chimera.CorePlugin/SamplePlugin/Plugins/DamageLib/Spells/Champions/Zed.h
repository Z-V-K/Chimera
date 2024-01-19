#pragma once
#include "../DamageChamp.h"

class Zed : public DamageChamp
{
public:
	Zed(GameObject* source) : DamageChamp(source) { }

	const double RDamage[3] = { 0.25, 0.4, 0.55 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1.10 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + 0.65 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = 0.65 * src->get_total_ad() + RDamage[level];
		}

		return ret;
	}
};