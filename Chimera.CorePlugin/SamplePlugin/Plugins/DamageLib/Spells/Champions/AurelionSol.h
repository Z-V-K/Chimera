#pragma once
#include "../DamageChamp.h"

class AurelionSol : public DamageChamp
{
public:
	AurelionSol(GameObject* source) : DamageChamp(source)
	{

	}

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = (20 + level) + Q->base_damage[level] + .35 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 1 / 16 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .65 * src->get_ap();
		}

		return ret;
	}
};