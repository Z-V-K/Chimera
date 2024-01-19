#pragma once
#include "../DamagePassive.h"

struct OrnnPassive : DamagePassive
{
	OrnnPassive() : DamagePassive(CharacterHash::Ornn) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double val = (source->get_level() < 3 ? 7.0 : (source->get_level() < 6 ? 8.0 : (source->get_level() < 9 ? 9.0 : (source->get_level() < 12 ? 10.0 : (source->get_level() < 15 ? 11.0 : (source->get_level() < 18 ? 12.0 : 13.0)))))) / 100.0 * (double) target->get_max_health();

		return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x3397a88a);
	}
};