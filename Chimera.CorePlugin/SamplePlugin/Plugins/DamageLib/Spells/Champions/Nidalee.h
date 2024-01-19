#pragma once
#include "../DamageChamp.h"

class Nidalee : public DamageChamp
{
public:
	Nidalee(GameObject* source) : DamageChamp(source)
	{

	}

	double QRanged[5] = { 70, 90, 110, 130, 150 };
	double QMelee[4] = {5, 30, 55, 80};
	double QMeleePercent[4] = { 1, 1.25, 1.5, 1.75 };

	double WRangedTick[5] = { 10, 20, 30, 40, 50 };
	double WMeele[4] = { 60, 110, 160, 210 };

	double EMelee[4] = { 80, 140, 200, 260 };

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret{ 0, 0, 0 };

		const int cougarRank = src->get_spell(SlotId::R)->get_level();

		if (spellslot == SlotId::Q)
		{
			if (stage == 1)
				ret.magical = Q->base_damage[level] + 0.5 * src->get_ap();

			if (stage == 2)
			{
				int num = src->get_spell(SlotId::R)->get_level();
				if (num == 0)
					num = 1;
				ret.magical = (QMelee[num - 1] + 0.4 * (double)src->get_ap() + 0.75 * (double)src->get_total_ad()) * (((double)target->get_max_health() - (double)target->get_health()) / (double)target->get_max_health() * QMeleePercent[num - 1] + 1.0);
			}
		}

		if (spellslot == SlotId::W)
		{
			if (stage == 1)
				ret.magical = WRangedTick[level] + 0.05 * src->get_ap();

			if (stage == 2)
				ret.magical = WMeele[cougarRank] + 0.3 * src->get_ap();
		}

		if (spellslot == SlotId::E)
		{
			if (stage == 2)
				ret.magical = EMelee[cougarRank] + 0.45 * src->get_ap();
		}

		return ret;
	}
};