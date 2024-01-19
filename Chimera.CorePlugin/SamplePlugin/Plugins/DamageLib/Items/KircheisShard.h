#pragma once
#include "DamageItem.h"

struct KircheisShard : DamageItem
{
	KircheisShard() : DamageItem(ItemId::Kircheis_Shard, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 60.0, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0xc4266ca1) == 100;
	}
};