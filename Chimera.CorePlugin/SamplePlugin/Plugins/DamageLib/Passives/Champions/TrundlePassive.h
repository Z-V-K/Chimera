#pragma once
#include "../DamagePassive.h"

struct TrundlePassive : DamagePassive
{
	TrundlePassive() : DamagePassive(CharacterHash::Trundle) { }

	double damages[5]
	{
		20.0,
		40.0,
		60.0,
		80.0,
		100.0
	};

	double damagePercents[5]
	{
		0.1,
		0.2,
		0.3,
		0.4,
		0.5
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::Q);

		if (!spell || spell->get_level() == 0)
			return { };

		return { 0.0, damages[std::min(spell->get_level() - 1, 4)] + damagePercents[std::min(spell->get_level() - 1, 4)] * source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x82882666);
	}
};