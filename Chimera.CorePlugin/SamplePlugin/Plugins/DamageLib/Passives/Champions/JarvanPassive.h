#pragma once
#include "../DamagePassive.h"

struct JarvanPassive : DamagePassive
{
	JarvanPassive() : DamagePassive(CharacterHash::Janna) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		if (!target->is_minion() && !target->is_hero())
			return { };
		double damage = (double)target->get_health() * 0.08;
		if (target->is_minion())
			damage = std::min((double)target->get_health() * 0.08, 400.0);
		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return !target->has_buff(0x89d92fb7);
	}
};