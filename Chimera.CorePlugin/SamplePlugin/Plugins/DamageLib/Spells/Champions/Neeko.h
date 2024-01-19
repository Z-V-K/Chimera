#pragma once
#include "../DamageChamp.h"

class Neeko : public DamageChamp
{
public:
	Neeko(GameObject* source) : DamageChamp(source)
	{

	}

	double QMainDamage[5] = { 80, 125, 170, 215, 260 };

	double QMinorDamage[5] = { 35, 60, 85, 110, 145 };

	double QMonsterBonus[5] = { 35, 50, 65, 80, 95 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			double monsterBonusDamage = target->is_jungle_minion() ? QMonsterBonus[level] : 0;

			if (stage == 1)
				ret.magical = monsterBonusDamage + QMinorDamage[level] + .25 * src->get_ap();

			if (stage == 2)
				ret.magical = monsterBonusDamage + QMainDamage[level] + .5 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			ret.magical = E->base_damage[level] + 0.65 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.magical = R->base_damage[level] + 1.20 * src->get_ap();
		}

		return ret;
	}
};