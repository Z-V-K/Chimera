#pragma once
#include "../DamagePassive.h"

struct PoppyPassive : DamagePassive
{
	PoppyPassive() : DamagePassive(CharacterHash::Poppy) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double damage = 20.0;
		if (source->get_level() > 1)
			damage = 20.0 + 160.0 / 17.0 * (double)std::max(0, source->get_level() - 1);

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xb27e19bd);
	}
};