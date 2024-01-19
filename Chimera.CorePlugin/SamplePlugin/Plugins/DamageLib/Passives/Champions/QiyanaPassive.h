#pragma once
#include "../DamagePassive.h"

struct QiyanaPassive : DamagePassive
{
	QiyanaPassive() : DamagePassive(CharacterHash::Qiyana) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double val = (11 + 4 * source->get_level()) + 0.3 * (double)source->get_bonus_ad() + 0.3 * (double)source->get_ap();
		return { 0.0, val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return !target->has_buff(0x4a93863e) && !target->has_buff(0x8ebd78fa) && !target->has_buff(0xca970f72) && !target->has_buff(0x1e69518f);
	}
};