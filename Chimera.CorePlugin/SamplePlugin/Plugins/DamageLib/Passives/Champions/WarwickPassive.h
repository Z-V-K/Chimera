#pragma once
#include "../DamagePassive.h"

struct WarwickPassive : DamagePassive
{
	WarwickPassive() : DamagePassive(CharacterHash::Warwick) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 8.0 + 2.0 * source->get_level(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};