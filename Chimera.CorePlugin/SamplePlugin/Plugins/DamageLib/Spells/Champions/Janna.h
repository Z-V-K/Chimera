#pragma once
#include "../DamageChamp.h"

class Janna : public DamageChamp
{
public:
	Janna(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .35 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .6 * src->get_ap() + (src->get_level() >= 10 ? .35 : .25) * src->get_movement_speed();
		}

		return ret;
	}
};