#pragma once
#include "DamageItem.h"

struct InfinityForce : DamageItem
{
	InfinityForce() : DamageItem(ItemId::Infinity_Force, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, 2 * source->get_base_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x1fc8f39b);
	}
};