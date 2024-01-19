#pragma once
#include "../DamageChamp.h"

class Zoe : public DamageChamp
{
public:
	Zoe(GameObject* source) : DamageChamp(source) { }

	const double QDamage[5] = { 50, 80, 110, 140, 170 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			double baseDamage = 0;

			if (src->get_level() == 1)		baseDamage = 7;
			else if (src->get_level() == 2)	baseDamage = 8;
			else if (src->get_level() < 12)  baseDamage = (src->get_level() - 2) * 2 + 8;
			else if (src->get_level() < 16)  baseDamage = (src->get_level() - 11) * 3 + 26;
			else							baseDamage = (src->get_level() - 15) * 4 + 38;

			ret.magical = baseDamage + QDamage[level] + 0.6 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 0.13333333 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.45 * src->get_ap();
		}

		return ret;
	}
};