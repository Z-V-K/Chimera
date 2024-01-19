#pragma once
#include "../DamageChamp.h"

class Kassadin : public DamageChamp
{
public:
	Kassadin(GameObject* source) : DamageChamp(source) { }

	double RBuffDamage[3] = {
		35,
		45,
		55
	};

	const uint32_t hashRBuff = 0x930db3cf;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .7 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + .8 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + .85 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			const double num1 = R->base_damage[level] + .4 * src->get_ap() + .02 * src->get_max_mana();
			const double num2 = RBuffDamage[level] + .1 * src->get_ap() + .02 * src->get_max_mana();
			const double num3 = src->get_buff_count(hashRBuff) * num2;

			ret.magical = num1 + num3;
		}

		return ret;
	}
};