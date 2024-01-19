#pragma once
#include "../DamagePassive.h"

struct IreliaPassive : DamagePassive
{
	IreliaPassive() : DamagePassive(CharacterHash::Irelia) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 15.0 + 3.0 * (double)std::max(0, source->get_level() - 1) + 0.25 * (double)source->get_bonus_ad(), 0.0, 0.0};
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xd529084f);
	}
};