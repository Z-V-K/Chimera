#pragma once
#include "../DamagePassive.h"

struct ZoePassive : DamagePassive
{
	ZoePassive() : DamagePassive(CharacterHash::Zoe) { }

    double damages[18]
    {
        16.0,
        20.0,
        24.0,
        28.0,
        32.0,
        36.0,
        42.0,
        48.0,
        54.0,
        60.0,
        66.0,
        74.0,
        82.0,
        90.0,
        100.0,
        110.0,
        120.0,
        130.0
    };

    double damages2[5]
    {
        60.0,
        100.0,
        140.0,
        180.0,
        220.0
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        DamageOutput ret;

        if (source->has_buff(0x42427eaa))
            ret.magical += damages[std::min(17, std::max(0, source->get_level() - 1))] + 0.2 * (double)source->get_ap();

        if (source->has_buff(0x9979fc2b))
        {
            const auto spell = source->get_spell(SlotId::E);

            if (spell && spell->get_level() > 0)
                ret.magical += damages[std::min(spell->get_level() - 1, 4)] + 0.4 * (double)source->get_total_ad();
        }

        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x42427eaa) || source->has_buff(0x9979fc2b);
	}
};