#pragma once
#include "../DamageChamp.h"

class Katarina : public DamageChamp
{
public:
	Katarina(GameObject* source) : DamageChamp(source)
	{
		E->has_on_hit = true;
	}

	double R1Damage[3] = {
		375,
		562.5,
		750
	};

	double R2Damage[3] = {
		25,
		37.5,
		50
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .35 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .4 * src->get_total_ad() + .25 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + 2.85 * src->get_ap() + (2.25 + 1.485 * (1.0 / src->get_attack_delay()));
			if (stage == 2)
				ret.magical = R2Damage[level] + .19 * src->get_ap() + (.15 + .099 * 91 / src->get_attack_delay());
		}

		return ret;
	}
};