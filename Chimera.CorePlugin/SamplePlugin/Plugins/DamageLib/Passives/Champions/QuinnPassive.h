#pragma once
#include "../DamagePassive.h"

struct QuinnPassive : DamagePassive
{
	QuinnPassive() : DamagePassive(CharacterHash::Quinn) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, (10 + 5 * source->get_level()) + (0.14 + 0.02 * (double)source->get_level()) * (double)source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x307ca44f);
	}
};