#pragma once
#include "DamageItem.h"

struct EternalWinter : DamageItem
{
	EternalWinter() : DamageItem(ItemId::Eternal_Winter, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 100.0 + 0.3 * (double)source->get_ap(), 0.0, 0.0 };
	}

	DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { };
	}
};