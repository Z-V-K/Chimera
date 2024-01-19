#pragma once
#include "../DamagePassive.h"

struct TeemoPassive : DamagePassive
{
	TeemoPassive() : DamagePassive(CharacterHash::Teemo) { }

	double damages[5]
	{
		14.0,
		25.0,
		36.0,
		47.0,
		58.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::E);

		if (!spell || spell->get_level() == 0)
			return { };

		return { damages[std::min(spell->get_level() - 1, 4)] + .3 * source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};