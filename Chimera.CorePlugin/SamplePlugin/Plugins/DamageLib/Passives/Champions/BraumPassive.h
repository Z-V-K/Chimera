#pragma once
#include "../DamagePassive.h"

struct BraumPassive : DamagePassive
{
	BraumPassive() : DamagePassive(CharacterHash::Braum) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.2 * (double)(16 + 10 * source->get_level()), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x90fb6498);
	}
};