#pragma once
#include "../DamageChamp.h"

class Evelynn : public DamageChamp
{
public:
	Evelynn(GameObject* source) : DamageChamp(source)
	{
		E->has_on_hit = true;
	}

	double QBonusDamage[5] = {
		15,
		25,
		35,
		45,
		55
	};

	double E1Damage[5] = {
		55.0,
		70.0,
		85.0,
		100.0,
		115.0
	};

	double E2Damage[5] = {
		75.0,
		100.0,
		125.0,
		150.0,
		175.0
	};

	const uint32_t hashQDebuff = 0x086556b3;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .3 * src->get_ap();

			if (stage == 2 && target->has_buff(hashQDebuff))
				ret.magical = ret.magical + QBonusDamage[level] + .25 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .6 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1Damage[level] + (.03 + .015 * src->get_ap() / 100) * target->get_max_health();
			if (stage == 2)
				ret.magical = E2Damage[level] + (.04 + .025 * src->get_ap() / 100) * target->get_max_health();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .75 * src->get_ap();

			if (target->get_health_percent() <= 30)
				ret.magical *= 1.4;
		}

		return ret;
	}
};