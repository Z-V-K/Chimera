#pragma once
#include "../DamageChamp.h"

class KSante : public DamageChamp
{
public:
	KSante(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .4 * src->get_total_ad() + .3 * src->get_bonus_armor() + .3 * src->get_magic_pen_multiplier();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = target->is_hero() ? W->base_damage[level] * target->get_max_health() : (25 + 25 * src->get_level());
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .2 * src->get_total_ad();
		}

		return ret;
	}
};