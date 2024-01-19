#pragma once
#include "DamageItem.h"

struct DeadMansPlate : DamageItem
{
	DeadMansPlate() : DamageItem(ItemId::Dead_Mans_Plate, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		const auto charges = source->get_item(item_id)->get_stacks();
		return { 0.0, charges * .4 + charges * .01 * source->get_base_ad(), 0.0 };
	}
};