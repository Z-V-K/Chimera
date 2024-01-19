#pragma once
#include "DamageItem.h"

struct SeethingSorrow : DamageItem
{
	SeethingSorrow() : DamageItem(ItemId::Seething_Sorrow, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { source->get_crit() * 100 * 1.5 + 30.0, 0.0, 0.0 };
	}
};