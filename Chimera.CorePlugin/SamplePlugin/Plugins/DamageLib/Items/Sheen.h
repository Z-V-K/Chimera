#pragma once
#include "DamageItem.h"

struct Sheen : DamageItem
{
	Sheen() : DamageItem(ItemId::Sheen, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, source->get_base_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xedcbfd06);
	}
};