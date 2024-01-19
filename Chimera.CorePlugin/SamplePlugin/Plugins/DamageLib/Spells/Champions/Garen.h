#pragma once
#include "../DamageChamp.h"

class Garen : public DamageChamp
{
public:
	Garen(GameObject* source) : DamageChamp(source) { }

	double EDamage[5] = {
		4,
		8,
		12,
		16,
		20
	};

	double EDamagePercent[18] = {
		0.0,
		0.8,
		1.6,
		2.4,
		3.2,
		4.0,
		4.8,
		5.6,
		6.4,
		6.6,
		6.8,
		7.0,
		7.2,
		7.4,
		7.6,
		7.8,
		8.0,
		8.2
	};

	double ETotalDamagePercent[5] = {
		0.32,
		0.34,
		0.36,
		0.38,
		0.4
	};

	double RDamagePercent[3] = {
		0.25,
		0.3,
		0.35
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.physical = Q->base_damage[level] + .5 * src->get_total_ad();
		}

		if (spellslot == SlotId::E)
		{
			ret.physical = EDamage[level] + EDamagePercent[std::min((int)src->get_level() - 1, 17)] + ETotalDamagePercent[level] * src->get_total_ad();
		}

		if (spellslot == SlotId::R)
		{
			ret.raw = R->base_damage[level] + RDamagePercent[level] * (target->get_max_health() - target->get_health());
		}

		return ret;
	}
};