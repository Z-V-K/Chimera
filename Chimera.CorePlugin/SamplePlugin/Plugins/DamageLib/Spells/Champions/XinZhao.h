#pragma once
#include "../DamageChamp.h"

class XinZhao : public DamageChamp
{
public:
	XinZhao(GameObject* source) : DamageChamp(source) { }

	const double WSlash[5] = { 30, 30, 50, 60, 70 };
	const double WThrust[5] = { 50, 85, 120, 155, 190 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 0.4 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.physical = WSlash[level] + 0.3 * src->get_total_ad();

			if (stage == 2)
				ret.physical = WThrust[level] + 0.9 * src->get_total_ad() + 0.65 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.6 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + src->get_bonus_ad() + 1.1 * src->get_ap() + 0.15 * target->get_health();
		}

		return ret;
	}
};