#pragma once
#include "../DamagePassive.h"

struct MalphitePassive : DamagePassive
{
	MalphitePassive() : DamagePassive(CharacterHash::Malphite) { }

	double damages[5]
	{
		 15.0,
		25.0,
		35.0,
		45.0,
		55.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::W);

		const auto val = damages[std::min(spell->get_level() - 1, 4)] + 0.3 * (double)source->get_ap() + 0.15 * (double)source->get_armor();

		return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf5b1c1fb);
	}
};