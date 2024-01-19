#pragma once
#include "../DamagePassive.h"

struct OriannaPassive : DamagePassive
{
    OriannaPassive() : DamagePassive(CharacterHash::Orianna) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

	double damages[18]
	{
        10.0,
        12.35,
        14.71,
        17.06,
        19.41,
        21.76,
        24.12,
        26.47,
        28.82,
        31.18,
        33.53,
        35.88,
        38.24,
        40.59,
        42.94,
        45.29,
        47.65,
        50.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        double val = damages[std::min(17, source->get_level() - 1)] + .15 * source->get_ap();

        return { val, 0.0, 0.0 };
	}

    bool is_active(GameObject* source, GameObject* target) override
	{
        return true;
	}
};