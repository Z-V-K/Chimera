#pragma once
#include "../DamageChamp.h"

class Malzahar : public DamageChamp
{
public:
	Malzahar(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .55 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .8 * src->get_ap() + 2.5 * (.025 * src->get_ap() / 100) * target->get_max_health();
		}

		return ret;
	}
};