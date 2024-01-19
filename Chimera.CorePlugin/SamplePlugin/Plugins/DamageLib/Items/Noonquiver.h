#pragma once
#include "DamageItem.h"

struct Noonquiver : DamageItem
{
	Noonquiver() : DamageItem(ItemId::Noonquiver, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, 20.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_item(item_id) != nullptr && target->is_minion();
	}
};