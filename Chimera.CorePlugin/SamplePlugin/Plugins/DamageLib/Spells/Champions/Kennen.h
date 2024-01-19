#pragma once
#include "../DamageChamp.h"

class Kennen : public DamageChamp
{
public:
	Kennen(GameObject* source) : DamageChamp(source) { }

	double W1Damage[5] = {
		35,
		45,
		55,
		65,
		75
	};

	double W1DamagePercent[5] = {
		.8,
		.9,
		1,
		1.1,
		1.2
	};

	double W2Damage[5] = {
		60,
		85,
		110,
		135,
		160
	};

	double R1Damage[3] = {
		300,
		562.5,
		825
	};

	double R2Damage[3] = {
		40,
		75,
		110
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .85 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = W1Damage[level] + W1DamagePercent[level] * src->get_bonus_ad() + .35 * src->get_ap();
			if (stage == 2)
				ret.magical = W2Damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + 27 / 16 * src->get_ap();
			if (stage == 2)
				ret.magical = R2Damage[level] + .225 * src->get_ap();
		}

		return ret;
	}
};