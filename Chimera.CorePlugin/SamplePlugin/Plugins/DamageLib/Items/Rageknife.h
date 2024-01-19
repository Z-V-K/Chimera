#pragma once
#include "DamageItem.h"

struct Rageknife : DamageItem
{
	Rageknife() : DamageItem(ItemId::Rageknife, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 20, 0.0, 0.0 };
	}
};