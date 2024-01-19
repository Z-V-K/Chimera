#pragma once
#include "../DamageChamp.h"

class Yone : public DamageChamp
{
public:
	Yone(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	const std::pair<double, double> WDamage[5] =
	{
		{5, 0.055},
		{10, 0.06},
		{15, 0.065},
		{20, 0.07 },
		{25, 0.075}
	};

	const double RDamage[3] = { 100, 200, 300 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1.05 * src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			const double damage = WDamage[level].first + WDamage[level].second * target->get_max_health();
			const double monsterMax = 140 * src->get_level() * 10;
			double minionMin = 0;

			if		(src->get_level() < 9)	minionMin += src->get_level() * 10;
			else if (src->get_level() < 14)	minionMin += 110 + (src->get_level() - 8) * 20;
			else							minionMin += 210 + (src->get_level() - 13) * 40;

			ret.physical = damage;
			ret.magical = damage;

			if (target->is_minion())
			{
				if (damage < minionMin)
				{
					ret.physical = minionMin;
					ret.magical = minionMin;
				}
			}

			if (target->is_jungle_minion())
			{
				if (damage > monsterMax)
				{
					ret.physical = monsterMax;
					ret.magical = monsterMax;
				}
			}
		}

		if (spellslot == SlotId::E)
		{

		}

		if (spellslot == SlotId::R)
		{
			const double damage = RDamage[level] + 0.4 * src->get_total_ad();

			ret.magical = damage;
			ret.physical = damage;
		}

		return ret;
	}
};