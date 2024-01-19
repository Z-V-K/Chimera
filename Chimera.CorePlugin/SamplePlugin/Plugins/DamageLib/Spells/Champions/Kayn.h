#pragma once
#include "../DamageChamp.h"

class Kayn : public DamageChamp
{
public:
	Kayn(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		75,
		95,
		115,
		135,
		155
	};

	double Q2Damage[5] = {
		140,
		170,
		210,
		250,
		290
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + .8 * src->get_bonus_ad() + (!target->is_hero() ? 40 : 0);
			if (stage == 2)
				ret.physical = Q2Damage[level] + 1.3 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + 1.3 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.physical = R->base_damage[level] + 1.75 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = (.1 + .13 * src->get_bonus_ad() / 100) * target->get_max_health();
		}

		return ret;
	}
};