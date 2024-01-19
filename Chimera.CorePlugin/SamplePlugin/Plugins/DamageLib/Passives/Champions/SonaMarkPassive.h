#pragma once
#include "../DamagePassive.h"

struct SonaMarkPassive : DamagePassive
{
	SonaMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	double damages[5]
	{
		10.0,
		15.0,
		20.0,
		25.0,
		30.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf791ac5a);
	}
};