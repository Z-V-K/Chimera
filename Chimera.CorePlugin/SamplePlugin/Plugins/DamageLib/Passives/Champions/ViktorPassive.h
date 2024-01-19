#pragma once
#include "../DamagePassive.h"

struct ViktorPassive : DamagePassive
{
	ViktorPassive() : DamagePassive(CharacterHash::Viktor) { }

	double damages[5]
	{
		20.0,
		45.0,
		70.0,
		95.0,
		120.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::Q);

		if (!spell || spell->get_level() == 0)
			return { };

		return { damages[std::min(spell->get_level() - 1, 4)] + 0.55 * (double)source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x98cb6192);
	}
};