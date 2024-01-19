#pragma once
#include "../DamagePassive.h"

struct ElisePassive : DamagePassive
{
	ElisePassive() : DamagePassive(CharacterHash::Elise) { }

	double damages[3]
	{
		10,
		20,
		30
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		auto spell = source->get_spell(SlotId::R);
		if (spell && spell->get_level() > 0)
			ret.magical = damages[std::min(spell->get_level() - 1, 2)] + .2 * source->get_ap();
		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x93251bfb);
	}
};