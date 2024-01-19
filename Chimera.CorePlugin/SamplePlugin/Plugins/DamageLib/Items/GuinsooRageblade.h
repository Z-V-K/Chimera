#pragma once
#include "DamageItem.h"

struct GuinsooRageblade : DamageItem
{
	GuinsooRageblade() : DamageItem(ItemId::Guinsoos_Rageblade, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { source->get_crit() * 100 * 1.5 + 30.0, 0.0, 0.0 };
	}
};