#pragma once
#include "../DamageChamp.h"

class DrMundo : public DamageChamp
{
public:
	DrMundo(GameObject* source) : DamageChamp(source) { }

	double QMinDamage[5] = {
		80.0,
		135.0,
		190.0,
		245.0,
		300.0
	};

	double QMaxDamage[5] = {
		150.0,
		225.0,
		300.0,
		375.0,
		450.0
	};

	double QDamage[5] = {
		20.0,
		22.5,
		25.0,
		27.5,
		30.0
	};

	double EMaxDamage[5] = {
		15,
		20,
		25,
		30,
		35
	};

	double EDamage[5] = {
		15,
		20,
		25,
		30,
		35
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = QDamage[level] / 100 * target->get_health();

			if (target->is_minion() && target->is_neutral())
				ret.magical = std::min(QMaxDamage[level], std::max(QMinDamage[level], ret.magical));

			ret.magical = std::max(QMinDamage[level], ret.magical);
		}

		if (spellslot == SlotId::W)
		{
			ret.magical = W->base_damage[level] + 0.070000000298023224 * src->get_bonus_health();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = std::min(std::round(100.f - src->get_health_percent()), 40.f);
			ret.physical = std::min(EDamage[std::min(level, 4)] * (1 + ret.physical * .015), EMaxDamage[std::min(level, 4)]);
		}

		return ret;
	}
};