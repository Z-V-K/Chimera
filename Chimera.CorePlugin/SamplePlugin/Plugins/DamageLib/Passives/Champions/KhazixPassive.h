#pragma once
#include "../DamagePassive.h"

struct KhazixPassive : DamagePassive
{
	KhazixPassive() : DamagePassive(CharacterHash::Khazix) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double val = (6 + 8 * (source->get_level() - 1)) + 0.4 * (double)source->get_bonus_ad();

		return { 0.0, val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x97277675) && target->is_hero();
	}
};