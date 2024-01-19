#pragma once
#include "../DamagePassive.h"

struct ShacoPassive : DamagePassive
{
	ShacoPassive() : DamagePassive(CharacterHash::Shaco) { }

	double damages[5]
	{
		10.0,
		20.0,
		30.0,
		40.0,
		50.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Q);
		double damage = spell && spell->get_level() > 0 ? damages[std::min(spell->get_level() - 1, 4)] + 0.4 * (double)source->get_bonus_ad() + 0.3 * (double)source->get_ap() : 0.0;

		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x22c648a0);
	}
};