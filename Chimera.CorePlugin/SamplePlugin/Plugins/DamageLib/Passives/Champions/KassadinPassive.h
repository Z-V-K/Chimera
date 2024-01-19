#pragma once
#include "../DamagePassive.h"

struct KassadinPassive : DamagePassive
{
	KassadinPassive() : DamagePassive(CharacterHash::Kassadin) { }

	double damages[5]
	{
		70.0,
		95.0,
		120.0,
		145.0,
		170.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::W);
		return { spell && spell->get_level() > 0 ? 20.0 + 0.1 * (double)source->get_ap() + (source->has_buff(0x0ab7ed63) ? damages[std::min(spell->get_level() - 1, 4)] + 0.8 * (double)source->get_ap() : 0.0) : 0.0, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_spell(SlotId::W)->get_level() > 0;
	}
};