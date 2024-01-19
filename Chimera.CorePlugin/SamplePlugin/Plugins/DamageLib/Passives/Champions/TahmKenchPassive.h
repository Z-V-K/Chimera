#pragma once
#include "../DamagePassive.h"

struct TahmKenchPassive : DamagePassive
{
	TahmKenchPassive() : DamagePassive(CharacterHash::TahmKench) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { (8 + 3 * (source->get_level() - 1)) + .025 * source->get_bonus_health(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};