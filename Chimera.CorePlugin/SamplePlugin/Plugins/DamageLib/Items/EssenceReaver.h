#pragma once
#include "DamageItem.h"

struct EssenceReaver : DamageItem
{
	EssenceReaver() : DamageItem(ItemId::Essence_Reaver, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, 1.3 * source->get_base_ad() + .2 * source->get_bonus_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_item(item_id) != nullptr && source->has_buff(0xa08d5f4c);
	}
};