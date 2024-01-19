#pragma once

struct DamageItem
{
	ItemId item_id;
	DamageType damageType;

	DamageItem(ItemId itemId, DamageType damage_type) : item_id(itemId), damageType(damage_type) { }
	virtual ~DamageItem() = default;

	virtual DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) = 0;

	virtual DamageOutput get_passive_damage(GameObject* source, GameObject* target, bool is_auto)
	{
		return get_damage(source, target, is_auto);
	};

	virtual bool is_active(GameObject* source, GameObject* target)
	{
		return source->get_item(item_id) != nullptr;
	};
};