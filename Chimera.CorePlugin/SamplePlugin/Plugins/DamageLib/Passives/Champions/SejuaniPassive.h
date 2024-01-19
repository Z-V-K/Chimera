#pragma once
#include "../DamagePassive.h"

struct SejuaniPassive : DamagePassive
{
	SejuaniPassive() : DamagePassive(CharacterHash::Sejuani) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        double damage = 0.0;
        if (target->is_hero())
            damage = source->get_level() >= 7 ? (source->get_level() >= 14 ? 0.2 * (double)target->get_max_health() : 0.15 * (double)target->get_max_health()) : 0.1 * (double)target->get_max_health();
        if (target->is_minion())
            damage = 300.0;

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xa3931e3a);
	}
};