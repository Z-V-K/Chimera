#pragma once
#include "../DamageChamp.h"

class Xerath : public DamageChamp
{
public:
	Xerath(GameObject* source) : DamageChamp(source) { }

	const double WDamage[5] = { 60, 95, 130, 165, 200 };
	const double WCenter[5] = { 100.02, 158.365, 216.71, 275.055, 333.4 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.85 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = WDamage[level] + 0.6 * src->get_ap();

			if (stage == 2)
				ret.magical = WCenter[level] + 1.0002 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.45 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 0.45 * src->get_ap();
		}

		return ret;
	}
};