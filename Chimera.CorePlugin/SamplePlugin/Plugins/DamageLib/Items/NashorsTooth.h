#pragma once
#include "DamageItem.h"

struct NashorsTooth : DamageItem
{
	NashorsTooth() : DamageItem(ItemId::Nashors_Tooth, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 15 + .2 * source->get_ap(), 0.0 , 0.0 };
	}
};