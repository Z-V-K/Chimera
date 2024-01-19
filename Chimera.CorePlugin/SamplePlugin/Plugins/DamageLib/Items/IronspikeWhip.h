#pragma once
#include "DamageItem.h"

struct IronspikeWhip : DamageItem
{
	IronspikeWhip() : DamageItem(ItemId::Ironspike_Whip, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, source->get_base_ad(), 0.0 };
	}

	DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { };
	}
};