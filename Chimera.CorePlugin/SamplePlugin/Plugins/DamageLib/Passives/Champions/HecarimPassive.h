#pragma once
#include "../DamagePassive.h"

struct HecarimPassive : DamagePassive
{
	HecarimPassive() : DamagePassive(CharacterHash::Hecarim) { }

	double damages[5]
	{
		45.0,
		75.0,
		105.0,
		135.0,
		165.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, damages[std::min(source->get_spell(SlotId::E)->get_level() - 1, 4)] + 0.5 * (double)source->get_bonus_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x7882b129);
	}
};