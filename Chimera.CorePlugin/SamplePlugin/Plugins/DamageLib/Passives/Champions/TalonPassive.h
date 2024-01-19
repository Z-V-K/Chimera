#pragma once
#include "../DamagePassive.h"

struct TalonPassive : DamagePassive
{
	TalonPassive() : DamagePassive(CharacterHash::Talon) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, (65 + 10 * (source->get_level() - 1)) + 2.0 * source->get_bonus_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_buff_count(0x92cc1c50) == 3;
	}
};