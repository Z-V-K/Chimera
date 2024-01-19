#pragma once
#include "DamageItem.h"

struct DivineSunderer : DamageItem
{
	DivineSunderer() : DamageItem(ItemId::Divine_Sunderer, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		double dmg = 1.6 * source->get_base_ad() + (source->is_melee() ? .04 : .02) * target->get_max_health();
		return { 0.0, (target->is_jungle_minion() ? std::min(2.5 * source->get_base_ad(), dmg) : dmg), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_item(item_id) && source->has_buff(0xd3350c19);
	}
};