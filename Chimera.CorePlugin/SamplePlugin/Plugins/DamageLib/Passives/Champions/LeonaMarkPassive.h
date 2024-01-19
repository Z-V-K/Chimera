#pragma once
#include "../DamagePassive.h"

struct LeonaMarkPassive : DamagePassive
{
	LeonaMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 18 + 7 * source->get_level(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		if (const auto buff = target->get_buff(0xe0c2ffb4))
		{
			if (buff->get_caster() != source)
				return true;
		}

		return false;
	}
};