#pragma once
#include "../DamageChamp.h"

class Malphite : public DamageChamp
{
public:
	Malphite(GameObject* source) : DamageChamp(source) { }

	double WDamage[5] = {
		30,
		40,
		50,
		60,
		70
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = WDamage[level] + .2 * src->get_ap() + .15 * src->get_armor();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .6 * src->get_ap() + .4 * src->get_armor();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .9 * src->get_ap();
		}

		return ret;
	}
};