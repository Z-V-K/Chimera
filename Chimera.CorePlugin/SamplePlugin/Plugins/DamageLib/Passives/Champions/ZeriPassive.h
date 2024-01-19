#pragma once
#include "../DamagePassive.h"
#include "../../DamageLib.h"

struct ZeriPassive : DamagePassive
{
    ZeriPassive() : DamagePassive(CharacterHash::Zeri) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

    double damages[19]
    {
        0.01,
        0.0159,
        0.021,
        0.0287,
        0.0354,
        17.0 / 400.0,
        0.0499,
        36.0 / 625.0,
        0.0655,
        0.0737,
        0.0823,
        0.0911,
        0.1002,
        0.1096,
        0.1192,
        0.1292,
        0.1395,
        0.15,
        0.15
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        int val1 = source->get_level() - 1;
        double num1 = 281.0 / 400.0 + 7.0 / 400.0 * (double)val1;
        if (source->has_buff(0x016e7450))
            return { 90.0 + 110.0 / 17.0 * (double)val1 * num1 + 0.9 * (double)source->get_ap() + damages[std::min(val1, 17)] * (double)target->get_max_health() / 100.0, 0.0, 0.0 };
        double num2 = 10.0 + 15.0 / 17.0 * (double)val1 * num1 + 0.03 * (double)source->get_ap();

        double dmg = target->is_minion() && (double)target->get_health() - 10.0 < DamageLib::compute_magical_damage(source, target, num2 * 6.0) ? (double)target->get_max_health() : num2;
        return { dmg, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
        return true;
	}
};