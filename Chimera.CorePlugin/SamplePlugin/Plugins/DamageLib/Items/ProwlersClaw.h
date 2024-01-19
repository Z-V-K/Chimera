#pragma once
#include "DamageItem.h"

struct ProwlersClaw : DamageItem
{
	ProwlersClaw() : DamageItem(ItemId::Prowlers_Claw, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		double damage = source->is_melee() ? 85 : 65 + (source->is_melee() ? .55 : .35 * source->get_bonus_ad());
		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_item(item_id) && source->has_buff(buff_hash("6693ready"));
	}
};