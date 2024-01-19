#pragma once
#include "../DamagePassive.h"

struct SkarnerPassve : DamagePassive
{
	SkarnerPassve() : DamagePassive(CharacterHash::Skarner) { }

	double damages[5]
	{
		30.0,
		50.0,
		70.0,
		90.0,
		110.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::E);

		if (!spell || spell->get_level() == 0)
			return { };

		return { 0.0, damages[std::min(spell->get_level() - 1, 4)], 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x19a4ba2f);
	}
};