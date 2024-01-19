#pragma once
#include "../DamagePassive.h"

struct JaxPassive : DamagePassive
{
	JaxPassive() : DamagePassive(CharacterHash::Jax) { }

	double damages[5]{
		50.0,
		85.0,
		120.0,
		155.0,
		190.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { damages[std::min(source->get_spell(SlotId::W)->get_level() - 1, 4)] + 0.6 * (double)source->get_ap(), 0.0, 0.0};
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xad19d8b3);
	}
};