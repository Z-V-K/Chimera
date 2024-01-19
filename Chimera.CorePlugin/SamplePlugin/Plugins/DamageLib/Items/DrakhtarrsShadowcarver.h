#pragma once
#include "DamageItem.h"

struct DrakhtarrsShadowcarver : DamageItem
{
	DrakhtarrsShadowcarver() : DamageItem(ItemId::Draktharrs_Shadowcarver, DamageType::Physical) { }

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return { 0.0, (source->is_melee() ? 75.0 : 55.0) + (source->is_melee() ? 0.3 : 0.25) * (double)source->get_bonus_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		const auto item = source->get_item(item_id);
		return item && source->get_item_spell_slot(item_id)->get_ready_at() < game_time->get_time() && target->is_hero();
	}
};