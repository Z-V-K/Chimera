#pragma once
#include "../DamagePassive.h"

struct RekSaiPassive : DamagePassive
{
	RekSaiPassive() : DamagePassive(CharacterHash::RekSai) { }

	double damages[5]
	{
		20.0,
		25.0,
		30.0,
		35.0,
		40.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::Q);

		if (spell->get_level() < 1)
			return { };

		return { 0.0, damages[std::min(spell->get_level() - 1, 4)] + 0.5 * (double)source->get_bonus_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x50bdd79f);
	}
};