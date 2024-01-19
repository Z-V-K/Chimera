#pragma once
#include "../DamagePassive.h"

struct XayahMarkPassive : DamagePassive
{
	XayahMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, .2 * source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		if (!source->has_buff(0x4637426d))
			return false;

		return source->get_character_hash() == CharacterHash::Xayah || source->get_character_hash() == CharacterHash::Rakan;
	}
};