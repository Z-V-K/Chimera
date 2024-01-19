#pragma once
#include "DamageItem.h"

struct IcebornGauntlet : DamageItem
{
	IcebornGauntlet() : DamageItem(ItemId::Iceborn_Gauntlet, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, source->get_base_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		const auto item = source->get_item(item_id);
		return item && source->get_item_spell_slot(item_id)->get_ready_at() < game_time->get_time();
	}
};