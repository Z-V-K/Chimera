#pragma once
#include "../DamageChamp.h"

class Heimerdinger : public DamageChamp
{
public:
	Heimerdinger(GameObject* source) : DamageChamp(source) { }

	double W1Damage[5] = {
		90,
		135,
		180,
		225,
		270
	};

	double W2Damage[3] = {
		503,
		697.5,
		892
	};

	double E1Damage[5] = {
		60,
		100,
		140,
		180,
		220
	};

	double E2Damage[5] = {
		100,
		200,
		300
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = W1Damage[level] + .93 * src->get_ap();
			if (stage == 2)
				ret.magical = W2Damage[src->get_spell(SlotId::R)->get_level() - 1] + 1.83 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1Damage[level] + .6 * src->get_ap();
			if (stage == 2)
				ret.magical = E2Damage[src->get_spell(SlotId::R)->get_level() - 1] + .6 * src->get_ap();
		}

		return ret;
	}
};