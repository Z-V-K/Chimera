#pragma once
#include "../DamageChamp.h"

class Yorick : public DamageChamp
{
public:
	Yorick(GameObject* source) : DamageChamp(source) { }

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + 0.4 * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			const double minDamage = E->base_damage[level] + 0.7 * src->get_total_ad();
			const double damage = 0.15 * target->get_health();

			ret.magical = (damage < minDamage) ? minDamage : damage;
		}

		if (spellslot == SlotId::R)
		{

		}

		return ret;
	}
};