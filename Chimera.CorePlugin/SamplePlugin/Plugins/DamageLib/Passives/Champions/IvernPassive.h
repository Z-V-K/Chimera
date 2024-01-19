#pragma once
#include "../DamagePassive.h"

struct IvernPassive : DamagePassive
{
	IvernPassive() : DamagePassive(CharacterHash::Ivern) { }

	double damages[5]
	{
		30.0,
		37.5,
		45.0,
		52.5,
		60.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { damages[std::min(source->get_spell(SlotId::W)->get_level() - 1, 4)] + 0.3 * (double)source->get_ap(), 0.0, 0.0};
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf01991ab);
	}
};