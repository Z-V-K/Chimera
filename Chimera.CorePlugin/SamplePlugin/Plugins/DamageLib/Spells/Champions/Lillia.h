#pragma once
#include "../DamageChamp.h"

class Lillia : public DamageChamp
{
public:
	Lillia(GameObject* source) : DamageChamp(source) { }

	double W1Damage[5] = {
		80,
		100,
		120,
		140,
		160
	};

	double W2Damage[5] = {
		240,
		300,
		360,
		420,
		480
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .4 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = (W1Damage[level] + .35 * src->get_ap()) * (target->is_minion() ? .5 : 1);
			if (stage == 2)
				ret.magical = (W2Damage[level] + 1.05 * src->get_ap()) * (target->is_minion() ? .5 : 1);
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .45 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .4 * src->get_ap();
		}

		return ret;
	}
};