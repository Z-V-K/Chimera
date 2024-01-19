#pragma once
#include "../DamageChamp.h"

class Kalista : public DamageChamp
{
public:
	Kalista(GameObject* source) : DamageChamp(source) { }

	double WDamage[5] = {
		.14,
		.15,
		.16,
		.17,
		.18
	};

	double WMinDamage[5] = {
		75,
		125,
		150,
		175,
		200
	};

	double EDamage[5] = {
		20,
		30,
		40,
		50,
		60
	};

	double EBuffDamage[5] = {
		10,
		14,
		19,
		25,
		32
	};

	double EBuffDamagePercent[5] = {
		0.232,
		0.275,
		0.319,
		0.363,
		0.406
	};

	const uint32_t hashEBuff = 0x8074df9e;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = WDamage[level] * target->get_max_health();
			if (target->is_minion())
				ret.magical = std::min(WMinDamage[level], ret.magical);
		}

		if (spellslot == SlotId::E)
		{
			const int buffCount = target->get_buff_count(hashEBuff);

			const double num1 = EDamage[level] + .7 * src->get_total_ad() + .2 * src->get_ap();
			const double num2 = EBuffDamage[level] + EBuffDamagePercent[level] * src->get_total_ad() + .2 * src->get_ap();
			const double num3 = (buffCount - 1) * num2;

			ret.physical = num1 + num3;
		}

		return ret;
	}
};