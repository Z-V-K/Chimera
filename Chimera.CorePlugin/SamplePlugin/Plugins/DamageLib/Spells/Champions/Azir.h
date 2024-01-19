#pragma once
#include "../DamageChamp.h"

class Azir : public DamageChamp
{
public:
	Azir(GameObject* source) : DamageChamp(source)
	{

	}

	double WDamage[18] = {
		0.0,
		0.0,
		0.0,
		0.0,
		0.0,
		0.0,
		0.0,
		0.0,
		0.0,
		2.0,
		7.0,
		12.0,
		17.0,
		32.0,
		47.0,
		62.0,
		77.0,
		92.0
	};

	double WExtraDamage[5] = {
		50.0,
		67.0,
		84.0,
		101.0,
		118.0
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			ret.magical = Q->base_damage[level] + .35 * src->get_ap();
		}

		if (spellslot == SlotId::W)
		{
			const int lvl = std::min((int) src->get_level() - 1, 17);
			ret.magical = WDamage[lvl] + WExtraDamage[level] + .55 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + .75 * src->get_ap();
		}

		return ret;
	}
};