#pragma once
#include "../DamagePassive.h"

struct MonkeyKingPassive : DamagePassive
{
	MonkeyKingPassive() : DamagePassive(CharacterHash::MonkeyKing) { }

	double damages[5]
	{
		20.0,
		45.0,
		70.0,
		95.0,
		120.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::Q);

		const double val = damages[std::min(spell->get_level() - 1, 4)] + 0.45 * (double)source->get_bonus_ad();

		return { 0.0, val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x8bba64d6);
	}
};