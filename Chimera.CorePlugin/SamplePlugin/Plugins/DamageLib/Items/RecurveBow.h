#pragma once
#include "DamageItem.h"

struct RecurveBow : DamageItem
{
	RecurveBow() : DamageItem(ItemId::Recurve_Bow, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 15.0, 0.0, 0.0 };
	}
};