#pragma once
#include "../DamagePassive.h"

struct ShenPassive : DamagePassive
{
	ShenPassive() : DamagePassive(CharacterHash::Shen) { }

	double maxDamage[5]
	{
		75.0,
		100.0,
		125.0,
		150.0,
		175.0
	};

	double heroDamage[5]
	{
		0.04,
		0.045,
		0.05,
		0.055,
		0.06
	};

	double minionDamage[5]
	{
		0.02,
		0.025,
		0.03,
		0.035,
		0.04
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Q);
		if (!spell || spell->get_level() == 0)
			return { };

		int num1 = source->get_level() >= 16 ? 40 : (source->get_level() >= 13 ? 34 : (source->get_level() >= 10 ? 28 : (source->get_level() >= 7 ? 22 : (source->get_level() >= 4 ? 16 : 10))));
		double val1 = maxDamage[std::min(spell->get_level() - 1, 4)];
		if (source->has_buff(0xf2180bc2))
		{
			double num2 = (heroDamage[std::min(spell->get_level() - 1, 4)] + 0.02 * (double)source->get_ap() / 100.0) * (double)target->get_max_health();
			return { target->is_minion() && target->is_neutral() ? std::min(val1, (double)num1 + num2) : (double)num1 + num2, 0.0, 0.0 };
		}

		double num3 = (minionDamage[std::min(spell->get_level() - 1, 4)] + 0.015 * (double)source->get_ap() / 100.0) * (double)target->get_max_health();
		return { target->is_minion() && target->is_neutral() ? std::min(val1, (double)num1 + num3) : (double)num1 + num3, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x840a7481) || source->has_buff(0xf2180bc2);
	}
};