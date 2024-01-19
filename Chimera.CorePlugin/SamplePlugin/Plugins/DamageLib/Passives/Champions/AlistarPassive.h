#pragma once
#include "../DamagePassive.h"

struct AlistarPassive : DamagePassive
{
	AlistarPassive() : DamagePassive(CharacterHash::Alistar) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const double val = 20 + 15 * (source->get_level() - 1);

		return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xc9742fd2);
	}
};