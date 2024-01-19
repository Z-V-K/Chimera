#pragma once
#include "../DamageChamp.h"

class Fizz : public DamageChamp
{
public:
	Fizz(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
	}

	double R1Damage[3] = {
		150,
		250,
		350
	};

	double R2Damage[3] = {
		225,
		325,
		425
	};

	double R3Damage[3] = {
		300,
		400,
		500
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 1 * src->get_total_ad() + .55 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .5 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .9 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + .8 * src->get_ap();
			if (stage == 2)
				ret.magical = R2Damage[level] + 1 * src->get_ap();
			if (stage == 3)
				ret.magical = R3Damage[level] + 1.2 * src->get_ap();
		}

		return ret;
	}
};