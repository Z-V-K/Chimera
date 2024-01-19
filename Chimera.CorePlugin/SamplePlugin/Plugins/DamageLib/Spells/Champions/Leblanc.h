#pragma once
#include "../DamageChamp.h"

class Leblanc : public DamageChamp
{
public:
	Leblanc(GameObject* source) : DamageChamp(source) { }

	double Q1Damage[5] = {
		65,
		90,
		115,
		140,
		165
	};

	double Q2Damage[3] = {
		70,
		140,
		210
	};

	double W1Damage[5] = {
		75,
		115,
		155,
		195,
		235
	};

	double W2Damage[3] = {
		150,
		300,
		450
	};

	double E1Damage[5] = {
		50,
		70,
		90,
		110,
		130
	};

	double E2Damage[3] = {
		70,
		140,
		210
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = Q1Damage[level] + .4 * src->get_ap();
			if (stage == 2)
				ret.magical = Q2Damage[src->get_spell(SlotId::R)->get_level() - 1] + .4 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = W1Damage[level] + .6 * src->get_ap();
			if (stage == 2)
				ret.magical = W2Damage[src->get_spell(SlotId::R)->get_level() - 1] + .75 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1Damage[level] + .3 * src->get_ap();
			if (stage == 2)
				ret.magical = E2Damage[src->get_spell(SlotId::R)->get_level() - 1] + .4 * src->get_ap();
		}

		return ret;
	}
};