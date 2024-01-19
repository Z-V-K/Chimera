#pragma once
#include "../DamagePassive.h"

struct RammusPassive : DamagePassive
{
	RammusPassive() : DamagePassive(CharacterHash::Rammus) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 10, 0, 0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};