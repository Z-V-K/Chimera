#pragma once
#include "../DamagePassive.h"

struct SionPassive : DamagePassive
{
	SionPassive() : DamagePassive(CharacterHash::Sion) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double damage = 0.0;

		if (source->is_hero())
			damage = .1 * target->get_max_health();
		if (source->is_minion())
			damage = std::min(75.0, .1 * target->get_max_health());

		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xb600518b);
	}
};