#pragma once
#include "../DamagePassive.h"

struct BraumMarkPassive : DamagePassive
{
	BraumMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 16.0 + 10.0 * source->get_level(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_buff_count(0xee30d4cb) == 3;
	}
};