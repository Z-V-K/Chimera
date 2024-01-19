#pragma once
#include "../DamageChamp.h"

class BelVeth : public DamageChamp
{
public:
	BelVeth(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
		Q->on_hit_ratio = .75f;
		E->has_on_hit = true;
		E->on_hit_ratio = .6f;
	}

	double QMinionDamages[5] = {
		.6,
		.7,
		.8,
		.9,
		1
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret = { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 1.1 * src->get_total_ad();

			if (target->is_minion())
			{
				if (target->is_neutral())
					ret.physical *= QMinionDamages[level];
				else
					ret.physical *= 1.2;
			}
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 1 * src->get_bonus_ad() + 1.25 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .06 * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.raw = R->base_damage[level] + 1 * src->get_ap() + .25 * (target->get_max_health() - target->get_health());
		}

		return ret;
	}
};
