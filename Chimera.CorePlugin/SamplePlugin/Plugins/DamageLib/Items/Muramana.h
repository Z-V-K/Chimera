#pragma once
#include "DamageItem.h"

struct Muramana : DamageItem
{
	Muramana() : DamageItem(ItemId::Muramana, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		double damage;
		if (is_auto)
		{
			damage = .015 * source->get_max_mana();
		}
		else
		{
			damage = (source->is_melee() ? 0.035 : 0.027) * (double)source->get_max_mana() + 0.06 * (double)source->get_bonus_ad();
		}
		return { 0.0, damage, 0.0 };
	}

	DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, .015 * source->get_max_mana(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_item(item_id) != nullptr && target->is_hero();
	}
};