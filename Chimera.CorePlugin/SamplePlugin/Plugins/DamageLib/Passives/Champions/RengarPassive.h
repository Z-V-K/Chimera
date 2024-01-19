#pragma once
#include "../DamagePassive.h"

struct RengarPassive : DamagePassive
{
	RengarPassive() : DamagePassive(CharacterHash::Rengar) { }

	double damages[18]
	{
        30.0,
        45.0,
        60.0,
        75.0,
        90.0,
        105.0,
        120.0,
        135.0,
        150.0,
        160.0,
        170.0,
        180.0,
        190.0,
        200.0,
        210.0,
        220.0,
        230.0,
        240.0
	};

    double maxdamages[5]
    {
        30.0,
        60.0,
        90.0,
        120.0,
        150.0
    };

    double maxdamagePercents[5]
    {
        0.0,
        0.05,
        0.1,
        0.15,
        0.2
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        auto spell = source->get_spell(SlotId::Q);
        if (!spell || spell->get_level() < 1)
            return { };
        double damage = source->has_buff(0x162c88e7) ? maxdamages[std::min(spell->get_level() - 1, 4)] + maxdamagePercents[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad() : damages[std::min(source->get_level() - 1, 17)] + 0.4 * (double)source->get_total_ad();

        return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
        return source->has_buff(0x4e2e6243) || source->has_buff(0x162c88e7);
	}
};