#pragma once
#include "../DamagePassive.h"

struct ShyvanaPassive : DamagePassive
{
	ShyvanaPassive() : DamagePassive(CharacterHash::Shyvana) { }

	double damages[5]
	{
		0.2,
		0.35,
		0.5,
		0.65,
		0.8
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Q);
		if (!spell || spell->get_level() <= 0)
			return { };
		return { 0.0, source->has_buff(0x2cafce8b) ? damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad() + 0.25 * (double)source->get_ap() : damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad() * 2.0 + 0.35 * (double)source->get_ap(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf89157c0) || source->has_buff(0x2cafce8b);
	}
};