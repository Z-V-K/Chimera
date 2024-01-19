#pragma once
#include "../DamageChamp.h"

class Xayah : public DamageChamp
{
public:
	Xayah(GameObject* source) : DamageChamp(source) { }

	const double EDamage[5] = { 50, 60, 70, 80, 90 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 0.5 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::E)
		{
			const double critAmp = 0.75 * src->get_crit();
			const double damage = critAmp + (EDamage[level] + 0.6 * src->get_bonus_ad());

			ret.physical = (target->is_minion() ? 0.5 : 1.0) * damage;
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + src->get_bonus_ad();
		}

		return ret;
	}
};