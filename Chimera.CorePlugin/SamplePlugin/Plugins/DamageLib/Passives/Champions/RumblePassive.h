#pragma once
#include "../DamagePassive.h"

struct RumblePassive : DamagePassive
{
	RumblePassive() : DamagePassive(CharacterHash::Rumble) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { (20 + 5 * (source->get_level() - 1)) + 0.3 * (double)source->get_ap(), 0.0, 0.0};
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xe02cb280);
	}
};