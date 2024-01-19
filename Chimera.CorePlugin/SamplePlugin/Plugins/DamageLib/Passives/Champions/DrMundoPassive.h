#pragma once
#include "../DamagePassive.h"

struct DrMundoPassive : DamagePassive
{
	DrMundoPassive() : DamagePassive(CharacterHash::DrMundo) { }

	double basicdamages[5]
    {
        15.0,
        20.0,
        25.0,
        30.0,
        35.0
    };

	double maxdamages[5]
    {
        25.0,
        30.0,
        35.0,
        40.0,
        45.0
    };


	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        auto spell = source->get_spell(SlotId::E);
        if (!spell || spell->get_level() <= 0)
            return { 0.0, 0.0, 0.0 };
        double basicdamage = basicdamages[std::min(spell->get_level() - 1, 4)];
        double maxdamage = maxdamages[std::min(spell->get_level() - 1, 4)];
        double num = 1.0 + std::min(std::round(100.0 - (double)source->get_health_percent()), 40.0) * 0.015;
        return { 0.0, std::min(basicdamage * num, maxdamage), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
        return source->has_buff(0x35bf5c4d);
	}
};