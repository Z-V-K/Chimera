#pragma once
#include "../DamageChamp.h"

class KogMaw : public DamageChamp
{
public:
	KogMaw(GameObject* source) : DamageChamp(source) { }

	double WDamage[5] = {
		.035,
		17 / 400,
		.05,
		23 / 400,
		.065
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = (WDamage[level] + .01 * (src->get_ap() / 100)) * target->get_max_health();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = (R->base_damage[level] + .65 * src->get_bonus_ad() + .35 * src->get_ap()) * (target->get_health_percent() < 25 ? 3 : (target->get_health_percent() < 50 ? 2 : 1));
		}

		return ret;
	}
};