#pragma once
#include "../DamageChamp.h"

class Anivia : public DamageChamp
{
public:
	Anivia(GameObject* source) : DamageChamp(source)
	{
		Q->has_stages = true;
		Q->stages = 2;
	}

	double Q1Damage[5] = {
		50,
		70,
		90,
		110,
		130
	};

	double Q2Damage[5] = {
		60,
		95,
		130,
		165,
		200
	};

	const uint32_t buffChilled = 0xbb41bbcc;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = Q1Damage[level] + .25 * src->get_ap();

			if (stage == 2)
				ret.magical = Q2Damage[level] + .45 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = (E->base_damage[level] + .6 * src->get_ap()) * (target->has_buff(buffChilled) ? 2 : 1);
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .125 * src->get_ap();
		}

		return ret;
	}
};