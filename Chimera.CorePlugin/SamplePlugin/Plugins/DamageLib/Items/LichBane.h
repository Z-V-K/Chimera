#pragma once
#include "DamageItem.h"

struct LichBane : DamageItem
{
	LichBane() : DamageItem(ItemId::Lich_Bane, DamageType::Magical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.75 * (double)source->get_base_ad() + 0.5 * (double)source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x15bf0b89);
	}
};