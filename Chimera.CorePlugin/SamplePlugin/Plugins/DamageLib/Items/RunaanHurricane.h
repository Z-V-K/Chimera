#pragma once
#include "DamageItem.h"

struct RunaanHurricane : DamageItem
{
	RunaanHurricane() : DamageItem(ItemId::Runaans_Hurricane, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 30.0, 0.0, 0.0 };
	}
};