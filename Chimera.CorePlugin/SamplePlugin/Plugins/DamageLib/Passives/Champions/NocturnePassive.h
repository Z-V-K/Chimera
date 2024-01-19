#pragma once
#include "../DamagePassive.h"

struct NocturnePassive : DamagePassive
{
	NocturnePassive() : DamagePassive(CharacterHash::Nocturne) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double val = 0.2 * (double) source->get_total_ad();
		return { 0.0, !target->is_minion() ? val : 0.5 * val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x43daf043);
	}
};