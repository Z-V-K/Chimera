#pragma once
#include "../DamagePassive.h"

struct SamiraPassive : DamagePassive
{
	SamiraPassive() : DamagePassive(CharacterHash::Samira) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double damage = ((double)(1 + source->get_level()) + 0.10000000149011612 * (double)source->get_bonus_ad()) * (((double)source->get_health_percent() + 100.0) / 100.0);

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_distance(source) < 200 + target->get_bounding_radius();
	}
};