#pragma once
#include "../DamagePassive.h"

struct YorickPassive : DamagePassive
{
	YorickPassive() : DamagePassive(CharacterHash::Yorick) { }

	double damages[5]
	{
		30.0,
		55.0,
		80.0,
		105.0,
		130.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::Q);

		if (!spell || spell->get_level() == 0)
			return { };

		return { 0.0, damages[std::min(spell->get_level() - 1, 4)] + .4 * source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x5774136c);
	}
};