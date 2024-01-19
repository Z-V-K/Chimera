#pragma once
#include "../DamagePassive.h"

struct LucianPassive : DamagePassive
{
	LucianPassive() : DamagePassive(CharacterHash::Lucian) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double num = source->get_level() < 6 ? 0.3 : (source->get_level() < 11 ? 0.4 : (source->get_level() < 16 ? 0.5 : 0.6));
		if (target->is_minion())
			num = 1.0;

		return { 0.0, (double)source->get_total_ad() * num, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xa38e6d27);
	}
};