#pragma once
#include "../DamageChamp.h"

class Zeri : public DamageChamp
{
public:
	Zeri(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	const std::pair<double, double> QDamage[5] =
	{
		{15, 1.04},
		{17, 1.08},
		{19, 1.12},
		{21, 1.16},
		{23, 1.20}
	};

	const double EDamageBonus[5] =
	{
		20, 22, 24, 26, 28
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = QDamage[level].first + QDamage[level].second * src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + 1.3 * src->get_total_ad() + 0.25 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + 0.85 * src->get_bonus_ad() + 1.1 * src->get_ap();
		}

		return ret;
	}
};