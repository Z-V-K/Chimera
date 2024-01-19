#pragma once

#include "../DamagePassive.h"

struct AatroxPassive : DamagePassive
{
	AatroxPassive() : DamagePassive(CharacterHash::Aatrox) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double val = (double)target->get_max_health() * (0.04 + 0.00047058823529411766 * (double) std::max(0, source->get_level() - 1));
		if (target->is_minion() && target->is_neutral())
			val = std::min(100.0, val);

		return { 0.0, val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x13a1401a);
	}
};