#pragma once
#include "../DamageChamp.h"

class Akshan : public DamageChamp
{
public:
	Akshan(GameObject* source) : DamageChamp(source)
	{
		Q->has_stages = true;
		Q->stages = 2;

		E->has_on_hit = true;
		E->on_hit_ratio = .25f;
	}

	double QDamagePercent[5] = {
		.4,
		.475,
		.55,
		.625,
		.7
	};

	double RDamagePercent[3] = {
		5,
		6,
		7
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q && (stage == 1 || stage == 2))
		{
			ret.physical = Q->base_damage[level] + .8 * src->get_total_ad();

			if (!target->is_hero())
				ret.physical = QDamagePercent[level] * ret.physical;
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = E->base_damage[level] + .175 * src->get_bonus_ad() + .3 * (src->get_attack_speed_multiplier() - 1.0) * 100;
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = (R->base_damage[level] + .1 * src->get_total_ad()) * (1 + (100 - target->get_health_percent()) * 0.029999999329447746) * RDamagePercent[level];
		}

		return ret;
	}
};