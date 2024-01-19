#pragma once
#include "../DamageChamp.h"

class Wukong : public DamageChamp
{
public:
	Wukong(GameObject* source) : DamageChamp(source) { }

	const double CloneDamageReduction[5] = { 0.35, 0.4, 0.45, 0.5, 0.55 };
	const double RCamp[3] = { 200, 400, 600 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = (Q->base_damage[level] + 0.45 * src->get_bonus_ad());
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = (E->base_damage[level] + src->get_ap());
		}

		if (spellslot == SlotId::R)
		{
			const double damage = (R->base_damage[level] * target->get_max_health() + 0.34375 * src->get_total_ad());
			ret.physical = target->is_jungle_minion() ? (damage > RCamp[level] ? RCamp[level] : damage) : damage;
		}

		return ret;
	}
};