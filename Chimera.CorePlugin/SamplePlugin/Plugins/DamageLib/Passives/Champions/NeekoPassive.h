#pragma once
#include "../DamagePassive.h"

struct NeekoPassive : DamagePassive
{
	NeekoPassive() : DamagePassive(CharacterHash::Neeko) { }

	double damages[5]
	{
		50.0,
		80.0,
		110.0,
		140.0,
		170.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::W);

		if (spell->get_level() == 0)
			return { };

		return { damages[std::min(spell->get_level() - 1, 4)] + 0.6 * (double)source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x7e98aa02);
	}
};