#pragma once
#include "../DamageChamp.h"

class Zac : public DamageChamp
{
public:
	Zac(GameObject* source) : DamageChamp(source) { }

	const std::pair<double, double> WDamage[5] =
	{
		{35, 0.04},
		{50, 0.05},
		{65, 0.06 },
		{80, 0.07},
		{05, 0.08}
	};

	const double WNonChampion[5] = { 235, 250, 265, 280, 295 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.3 * src->get_ap() + 0.03 * src->get_max_health();
		}

		if (spellslot == SlotId::W)
		{
			const double damage = WDamage[level].first + (WDamage[level].second + 0.03 * floor(src->get_ap() / 100)) * target->get_max_health();

			ret.magical = target->is_hero() ? damage : (damage > WNonChampion[level] ? WNonChampion[level] : damage);				
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.8 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 0.4 * src->get_ap();
		}

		return ret;
	}
};