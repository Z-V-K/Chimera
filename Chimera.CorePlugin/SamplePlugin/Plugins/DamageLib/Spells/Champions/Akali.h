#pragma once
#include "../DamageChamp.h"

class Akali : public DamageChamp
{
public:
	Akali(GameObject* source) : DamageChamp(source)
	{
		E->has_stages = true;
		E->stages = 2;

		R->has_stages = true;
		R->stages = 2;
	}

	double E1Damage[5] = {
		30,
		56.25,
		82.5,
		108.75,
		135
	};

	double E2Damage[5] = {
		70,
		131.25,
		192.25,
		253.75,
		315
	};

	double R1Damage[3] = {
		80,
		220,
		360
	};

	double R2Damage[3] = {
		60,
		130,
		200
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + 0.64999997615814209 * src->get_total_ad() + 0.60000002384185791 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 1)
				ret.magical = E1Damage[level] + 0.22499999403953552 * src->get_total_ad() + 0.40000000596046448 * src->get_ap();

			if (stage == 2)
				ret.magical = E2Damage[level] + 0.59500002861022949 * src->get_total_ad() + 0.8399999737739563 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + .5 * src->get_bonus_ad() + .3 * src->get_ap();

			if (stage == 2)
			{
				const double dmg = R2Damage[level] + .3 * src->get_ap();

				if (target->get_health_percent() <= 30.f)
					ret.magical = dmg * 2;
				else
					ret.magical = dmg * (2.8599998950958252 * (100 - target->get_health_percent()) / 100 + 1);
			}
		}

		return ret;
	}
};