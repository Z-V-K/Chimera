#pragma once
#include "../DamagePassive.h"

struct GragasPassive : DamagePassive
{
	GragasPassive() : DamagePassive(CharacterHash::Gragas) { }

	double damages[5]
	{
		20.0,
		50.0,
		80.0,
		110.0,
		140.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double damage = damages[std::min(source->get_spell(SlotId::W)->get_level() - 1, 4)] + 0.07 * (double)target->get_max_health() + 0.7 * (double)source->get_ap();

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf2b03514);
	}
};