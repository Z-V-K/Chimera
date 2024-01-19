#pragma once
#include "DamageItem.h"

struct DuskbladeOfDraktharr : DamageItem
{
	DuskbladeOfDraktharr() : DamageItem(ItemId::Duskblade_of_Draktharr, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		if (is_auto)
			return { };

		double pct_missing = (int)((((target->get_max_health() - target->get_health()) / target->get_max_health()) * 100) / 7);
		pct_missing = std::min(.7, pct_missing);
		double dmg = .018 * pct_missing;
		return { damageType == DamageType::Magical ? dmg : 0.0, damageType == DamageType::Physical ? dmg : 0.0 , damageType == DamageType::Raw ? dmg : 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_item(item_id);
	}
};