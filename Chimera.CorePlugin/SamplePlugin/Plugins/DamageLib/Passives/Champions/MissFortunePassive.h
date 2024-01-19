#pragma once
#include "../DamagePassive.h"

struct MissFortunePassive : DamagePassive
{
	MissFortunePassive() : DamagePassive(CharacterHash::MissFortune) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		if (target->has_buff(0xcef683ef))
			return { };

		double num = (double)source->get_total_ad() * (source->get_level() < 4 ? 0.25 : (source->get_level() < 7 ? 0.3 : (source->get_level() < 9 ? 0.35 : (source->get_level() < 11 ? 0.4 : (source->get_level() < 13 ? 0.45 : 0.5)))));
		return { 0.0, target->is_minion() ? num : num * 2.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};