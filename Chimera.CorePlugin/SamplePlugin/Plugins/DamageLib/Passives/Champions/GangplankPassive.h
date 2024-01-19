#pragma once
#include "../DamagePassive.h"

struct GangplankPassive : DamagePassive
{
	GangplankPassive() : DamagePassive(CharacterHash::Gangplank) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (target->is_minion())
			return ret;
		
		float damage = (float)(45 + 15 * std::min(18, source->get_level())) + source->get_bonus_ad();

		if (target->is_turret())
			damage *= 0.5f;

		ret.raw += damage;
		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x098de4eb);
	}
};