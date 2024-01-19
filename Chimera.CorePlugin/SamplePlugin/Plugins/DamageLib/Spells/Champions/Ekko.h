#pragma once
#include "../DamageChamp.h"

class Ekko : public DamageChamp
{
public:
	Ekko(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		60.0,
		75.0,
		90.0,
		105.0,
		120.0
	};

	double Q2Damage[5] = {
		40.0,
		65.0,
		90.0,
		115.0,
		140.0
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = Q1Damage[level] + .3 * src->get_ap();
			if (stage == 2)
				ret.magical = Q2Damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = (.03 + src->get_ap() / 100 * .03) * (target->get_max_health() - target->get_health());
			if (target->is_minion())
				ret.magical = std::min(150.0, std::max(15.0, ret.magical));
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .4 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1.75 * src->get_ap();
		}

		return ret;
	}
};