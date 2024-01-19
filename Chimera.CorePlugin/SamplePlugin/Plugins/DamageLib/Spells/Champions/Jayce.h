#pragma once
#include "../DamageChamp.h"

class Jayce : public DamageChamp
{
public:
	Jayce(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[6] = {
		60.0,
		110.0,
		160.0,
		210.0,
		260.0,
		310.0
	};

	double Q2Damage[6] = {
		55,
		110,
		165,
		220,
		275,
		330
	};

	double WDamage[6] = {
		35,
		50,
		65,
		80,
		95,
		1100
	};

	double EDamage[6] = {
		0.08,
		0.108,
		0.136,
		0.164,
		0.192,
		0.22
	};

	double EMaxDamage[6] = {
		200.0,
		300.0,
		400.0,
		500.0,
		600.0,
		700.0
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.physical = Q1Damage[level] + 1.2 * src->get_bonus_ad();
			if (stage == 2)
				ret.physical = Q2Damage[level] + 1.2 * src->get_bonus_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = WDamage[level] + .25 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = EDamage[level] * target->get_max_health() + 1 * src->get_bonus_ad();
			if (target->is_minion() && target->is_neutral())
				ret.magical = std::min(EMaxDamage[level], ret.magical);
		}

		return ret;
	}
};