#pragma once
#include "../DamagePassive.h"

struct SonaPassive : DamagePassive
{
	SonaPassive() : DamagePassive(CharacterHash::Sona) { }

	double damages[18]
	{
        20.0,
        30.0,
        40.0,
        50.0,
        60.0,
        70.0,
        80.0,
        90.0,
        105.0,
        120.0,
        135.0,
        150.0,
        165.0,
        180.0,
        195.0,
        210.0,
        225.0,
        240.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        return { damages[std::min(17, std::max(0, source->get_level() - 1))] + .2 * source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf27e43e3);
	}
};