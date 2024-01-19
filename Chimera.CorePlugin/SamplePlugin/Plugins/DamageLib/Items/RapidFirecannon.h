#pragma once
#include "DamageItem.h"

struct RapidFirecannon : DamageItem
{
	RapidFirecannon() : DamageItem(ItemId::Rapid_Firecannon, DamageType::Magical) { }


	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
        return { 60.0, 0.0, 0.0 };
	}

    bool is_active(GameObject* source, GameObject* target) override
	{
        return source->get_buff_count(buff_hash("itemstatikshankcharge")) == 100;
	}
};