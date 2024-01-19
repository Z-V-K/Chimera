#pragma once
#include "../DamagePassive.h"

struct VarusPassive : DamagePassive
{
	VarusPassive() : DamagePassive(CharacterHash::Varus) { }

	double damages[5]
	{
		7.0,
		12.0,
		17.0,
		22.0,
		27.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::W);

		if (!spell || spell->get_level() == 0)
			return { };

		return { damages[std::min(spell->get_level() - 1, 4)] + 0.3 * (double)source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};