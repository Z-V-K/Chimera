#pragma once
#include "../DamageChamp.h"

class Nautilus : public DamageChamp
{
public:
	Nautilus(GameObject* source) : DamageChamp(source)
	{

	}

	std::pair<double, double> RDamageMainTarget[3] = {
		{150, .8},
		{275, .8},
		{400, .8},
	};

	std::pair<double, double> RDamageMinorTarget[3] = {
		{125, .4},
		{175, .4},
		{225, .4},
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.9 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 0.4 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			double objectTypeScaling = target->is_jungle_minion() ? 1.5 : 1.0;
			ret.magical = objectTypeScaling * (E->base_damage[level] + 0.5 * src->get_ap());
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = RDamageMinorTarget[level].first + RDamageMinorTarget[level].second * src->get_ap();

			if (stage == 2)
				ret.magical = RDamageMainTarget[level].first + RDamageMainTarget[level].second * src->get_ap();
		}

		return ret;
	}
};