#pragma once
#include "../DamageChamp.h"

class Jhin : public DamageChamp
{
public:
	Jhin(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		0.35,
		0.425,
		0.5,
		0.575,
		0.65
	};

	double R1Damage[3] = {
		50,
		125,
		200
	};

	double R2Damage[3] = {
		100,
		250,
		400
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] * src->get_bonus_ad() + .6 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = W->base_damage[level] + .5 * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 1.2 * src->get_total_ad() + 1 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
			{
				ret.physical = R1Damage[level] + .25 * src->get_total_ad();
				ret.physical += ret.physical * std::min(3.0, ((100.0 - target->get_health_percent()) * 3.0));
			}

			if (stage == 2)
			{
				ret.physical = R2Damage[level] + .4 * src->get_total_ad();
				ret.physical += ret.physical + std::min(3.0, ((100.0 - target->get_health_percent()) * 3.0));
			}
		}

		return ret;
	}
};