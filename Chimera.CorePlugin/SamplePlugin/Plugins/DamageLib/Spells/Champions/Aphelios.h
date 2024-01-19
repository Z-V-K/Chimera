#pragma once
#include "../DamageChamp.h"

class Aphelios : public DamageChamp
{
public:
	Aphelios(GameObject* source) : DamageChamp(source)
	{
		Q->has_on_hit = true;
		Q->on_hit_ratio = .25f;
		R->has_on_hit = true;
	}

	double QCalibrumDamage[13] = {
		60.0,
		60.0,
		76.67,
		76.67,
		93.33,
		93.33,
		110.0,
		110.0,
		126.67,
		126.67,
		143.33,
		143.33,
		160.0
	};

	double QCalibrumDmgPercent[13] = {
		 0.42,
	     0.42,
	     0.45,
	     0.45,
	     0.48,
	     0.48,
	     0.51,
	     0.51,
	     0.54,
	     0.54,
	     0.57,
	     0.57,
	     0.6
	};

	double QCrescendumDamage[13] = {
		31.0,
		31.0,
		42.5,
		42.5,
		54.0,
		54.0,
		65.5,
		65.5,
		77.0,
		77.0,
		88.5,
		88.5,
		100.0
	};

	double QCrescendumDmgPercent[13] = {
		0.4,
		0.4,
		0.4333,
		0.4333,
		0.4667,
		0.4667,
		0.5,
		0.5,
		0.5333,
		0.5333,
		0.5337,
		0.5337,
		0.6
	};

	double QSeverumDamage[13] = {
		10.0,
		10.0,
		13.33,
		13.33,
		16.67,
		16.67,
		20.0,
		20.0,
		23.33,
		23.33,
		26.67,
		26.67,
		30.0
	};

	double QSeverumDmgPercent[13] = {
		0.21,
		0.21,
		0.225,
		0.225,
		0.24,
		0.24,
		0.255,
		0.255,
		0.27,
		0.27,
		0.285,
		0.285,
		0.3
	};

	double QGravitumDamage[13] = {
		50.0,
		50.0,
		60.0,
		60.0,
		70.0,
		70.0,
		80.0,
		80.0,
		90.0,
		90.0,
		100.0,
		100.0,
		110.0
	};

	double QGravitumDmgPercent[13] = {
		0.26,
		0.26,
		0.275,
		0.275,
		0.29,
		0.29,
		0.305,
		0.305,
		0.32,
		0.32,
		0.335,
		0.335,
		0.35
	};

	double QInfernumDamage[13] = {
		25.0,
		25.0,
		31.67,
		31.67,
		38.33,
		38.33,
		45.0,
		45.0,
		51.67,
		51.67,
		58.33,
		58.33,
		65.0
	};

	double QInfernumDmgPercent[13] = {
		0.56,
		0.56,
		0.6,
		0.6,
		0.64,
		0.64,
		0.68,
		0.68,
		0.72,
		0.72,
		0.76,
		0.76,
		0.8
	};

	DamageOutput get_damage(GameObject* target, SlotId spellslot, int level, int stage, int stacks) override
	{
		DamageOutput ret { 0, 0, 0 };

		if (spellslot == SlotId::Q)
		{
			const int lvl = std::min((int)src->get_level() - 1, 12);

			if (stage == 1)
				ret.physical = QCalibrumDamage[lvl] + QCalibrumDmgPercent[lvl] * src->get_bonus_ad() + 1 * src->get_ap();
			if (stage == 2)
				ret.physical = QSeverumDamage[lvl] + QSeverumDmgPercent[lvl] * src->get_bonus_ad();
			if (stage == 3)
				ret.physical = QGravitumDamage[lvl] + QGravitumDmgPercent[lvl] * src->get_bonus_ad() + .7 * src->get_ap();
			if (stage == 4)
				ret.physical = QInfernumDamage[lvl] + QInfernumDmgPercent[lvl] + .7 * src->get_ap();
			if (stage == 5)
				ret.physical = QCrescendumDamage[lvl] + QCrescendumDmgPercent[lvl] * src->get_bonus_ad() + .5 * src->get_ap();
		}

		if (spellslot == SlotId::R)
		{
			ret.physical = R->base_damage[level] + .2 * src->get_bonus_ad() + 1 * src->get_ap();
		}

		return ret;
	}
};