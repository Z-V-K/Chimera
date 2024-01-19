#pragma once
#include "../DamagePassive.h"

struct NasusPassive : DamagePassive
{
	NasusPassive() : DamagePassive(CharacterHash::Nasus) { }

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
		const auto spell = source->get_spell(SlotId::Q);

		const auto val = damages[std::min(spell->get_level() - 1, 4)] + (double)source->get_buff_count(0x16c42e4c);

		return { 0.0, val, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x16c42e4c);
	}
};