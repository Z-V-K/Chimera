#pragma once
#include "../DamageChamp.h"

class Yuumi : public DamageChamp
{
public:
	Yuumi(GameObject* source) : DamageChamp(source) { }

	const double QDamage[6] = { 60, 90, 120, 150, 180, 210 };
	const double QAttached[6] = { 80, 135, 190, 245,300, 355 };
	const double RDamage[3] = { 75, 100, 125 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = src->is_targetable() ? QDamage[level] + 0.2 * src->get_ap() : QAttached[level] + 0.35 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = RDamage[level] + 0.15 * src->get_ap();
		}

		return ret;
	}
};