#pragma once
#include "../DamageChamp.h"

class Gwen : public DamageChamp
{
public:
	Gwen(GameObject* source) : DamageChamp(source) { }

	double R1Damage[3] = {
		270,
		495,
		720
	};

	double R2Damage[3] = {
		35,
		65,
		95
	};

	double R3Damage[3] = {
		90,
		165,
		240
	};

	double R4Damage[3] = {
		150,
		275,
		400
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
			ret.magical = E->base_damage[level] + .08 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			if (stage == 1)
				ret.magical = R1Damage[level] + .72 * src->get_ap() + (.09 + src->get_ap() / 100 * .072) * target->get_max_health();
			if (stage == 2)
				ret.magical = R2Damage[level] + .08 * src->get_ap() + (.01 + src->get_ap() / 100 * 0.00800000037997961) * target->get_max_health();
			if (stage == 3)
				ret.magical = R3Damage[level] + .24 * src->get_ap() + (.03 + src->get_ap() / 100 * 0.024000000208616257) * target->get_max_health();
			if (stage == 4)
				ret.magical = R4Damage[level] + .4 * src->get_ap() + (.05 + src->get_ap() / 100 * 0.039999999105930328) * target->get_max_health();
		}

		return ret;
	}
};