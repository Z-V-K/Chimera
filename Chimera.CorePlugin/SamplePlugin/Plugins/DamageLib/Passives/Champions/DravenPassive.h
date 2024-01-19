#pragma once
#include "../DamagePassive.h"

struct DravenPassive : DamagePassive
{
	DravenPassive() : DamagePassive(CharacterHash::Draven) { }

     double damages[5]
    {
        40.0,
        45.0,
        50.0,
        55.0,
        60.0
    };
	double damagePercents[5]
    {
        0.7,
        0.8,
        0.9,
        1.0,
        1.1
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        auto spell = source->get_spell(SlotId::Q);

        if (!spell || spell->get_level() == 0)
            return { 0.0, 0.0, 0.0 };

        double damage = damages[std::min(spell->get_level()  - 1, 4)] + damagePercents[std::min(spell->get_level() - 1, 4)] * (double)source->get_bonus_ad();
        return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
        return source->has_buff(0x9b18596d);
	}
};