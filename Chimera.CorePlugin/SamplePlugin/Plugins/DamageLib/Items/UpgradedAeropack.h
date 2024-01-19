#pragma once
#include "DamageItem.h"

struct UpgradedAeropack : DamageItem
{
	UpgradedAeropack() : DamageItem(ItemId::Upgraded_Aeropack, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 125 + .15 * source->get_ap(), 0.0, 0.0 };
	}

	DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { };
	}
};