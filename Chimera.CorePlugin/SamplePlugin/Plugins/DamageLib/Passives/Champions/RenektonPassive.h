#pragma once
#include "../DamagePassive.h"

struct RenektonPassive : DamagePassive
{
	RenektonPassive() : DamagePassive(CharacterHash::Renekton) { }

	double damages[5]
	{
		15.0,
		45.0,
		75.0,
		105.0,
		135.0
	};

	double maxdamages[5]
	{
		10.0,
		30.0,
		50.0,
		70.0,
		90.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::W);
		if (!spell || spell->get_level() == 0)
			return { };
		double damage = damages[std::min(spell->get_level() - 1, 4)] + 1.25 * (double)source->get_total_ad();
		if ((double)source->get_mana() >= 50.0)
			damage = maxdamages[std::min(spell->get_level() - 1, 4)] + 0.5 * (double)source->get_total_ad();
		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x8a8e9043);
	}
};