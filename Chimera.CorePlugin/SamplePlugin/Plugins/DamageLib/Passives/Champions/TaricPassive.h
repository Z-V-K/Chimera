#pragma once
#include "../DamagePassive.h"

struct TaricPassive : DamagePassive
{
	TaricPassive() : DamagePassive(CharacterHash::Taric) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, (21 + 4 * (source->get_level() - 1)) + .15 * source->get_bonus_armor(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x24388a99);
	}
};