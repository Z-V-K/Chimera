#pragma once
#include "DamageItem.h"

struct Botrk : DamageItem
{
	Botrk() : DamageItem(ItemId::Blade_of_the_Ruined_King, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		double dmg = (source->is_melee() ? .12 : .09) * target->get_health();
		double val = target->is_minion() ? std::min(60.0, dmg) : std::max(15.0, dmg);
		return { 0.0, val, 0.0 };
	}
};