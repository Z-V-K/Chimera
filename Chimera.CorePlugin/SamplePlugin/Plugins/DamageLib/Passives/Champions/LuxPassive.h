#pragma once
#include "../DamagePassive.h"

struct LuxPassive : DamagePassive
{
	LuxPassive() : DamagePassive(CharacterHash::Lux) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { (10 + 10 * source->get_level()) + 0.2 * (double)source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		if (const auto buff = target->get_buff(0xa31beae9))
		{
			if (buff->get_caster() == source)
				return true;
		}

		return false;
	}
};