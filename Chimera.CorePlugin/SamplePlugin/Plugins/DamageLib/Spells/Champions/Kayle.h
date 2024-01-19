#pragma once
#include "../DamageChamp.h"

class Kayle : public DamageChamp
{
public:
	Kayle(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .6 * src->get_bonus_ad() + .5 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = (.08 + .01 * src->get_ap() / 50) * (target->get_max_health() - target->get_health());
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1 * src->get_bonus_ad() + .7 * src->get_ap();
		}

		return ret;
	}
};