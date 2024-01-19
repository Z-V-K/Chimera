#pragma once
#include "../DamageChamp.h"

class Karma : public DamageChamp
{
public:
	Karma(GameObject* source) : DamageChamp(source) { }

	double QDamage[5] = {
		70,
		120,
		170,
		220,
		270
	};

	double Q2Damage[5] = {
		70,
		120,
		170,
		220,
		270
	};

	double Q2RDamage[4] = {
		40,
		100,
		160,
		220
	};

	double WDamage[5] = {
		40,
		65,
		90,
		115,
		140
	};

	double W2Damage[5] = {
		80,
		130,
		180,
		230,
		280
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = QDamage[level] + .4 * src->get_ap();
			if (stage == 2)
				ret.magical = Q2Damage[level] + Q2RDamage[src->get_spell(SlotId::R)->get_level() - 1] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = WDamage[level] + .45 * src->get_ap();
			if (stage == 2)
				ret.magical = W2Damage[level] + .9 * src->get_ap();
		}

		return ret;
	}
};