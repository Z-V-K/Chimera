#pragma once
#include "../DamageChamp.h"

class Darius : public DamageChamp
{
public:
	Darius(GameObject* source) : DamageChamp(source) { }

	double QDamagePercent[5] = {
		1,
		1.1,
		1.2,
		1.3,
		1.4
	};

	double WDamage[5] = {
		1.4,
		1.45,
		1.5,
		1.55,
		1.6
	};

	uint32_t hashHemo = 0xf3f7bb00;

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + QDamagePercent[level] *src->get_total_ad();
		}

		if (spellslot == SlotId::W)
		{
			ret.physical = WDamage[level] * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .75 * src->get_bonus_ad();
			if(target->has_buff(hashHemo))
			{
				int buffCount = target->get_buff_count(hashHemo);
				ret.physical += ret.physical * buffCount * .2;
			}
		}

		return ret;
	}
};