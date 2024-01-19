#pragma once
#include "../DamagePassive.h"

struct VexPassive : DamagePassive
{
	VexPassive() : DamagePassive(CharacterHash::Vex) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { (30.0 + 150.0 / (17 * std::max(source->get_level() - 1, 1))), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x27d212a8);
	}
};