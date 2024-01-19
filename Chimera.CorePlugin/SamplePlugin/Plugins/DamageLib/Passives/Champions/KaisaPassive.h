#pragma once
#include "../DamagePassive.h"

struct KaisaPassive : DamagePassive
{
	KaisaPassive() : DamagePassive(CharacterHash::Kaisa) { }

     double firstDamage[20]
    {
        5.0,
        5.0,
        5.0,
        8.0,
        8.0,
        8.0,
        11.0,
        11.0,
        11.0,
        14.0,
        14.0,
        17.0,
        17.0,
        17.0,
        20.0,
        20.0,
        20.0,
        23.0,
        23.0,
        23.0
    };
     double secondDamage[20]
    {
        1.0,
        1.0,
        1.0,
        1.0,
        3.75,
        3.75,
        3.75,
        3.75,
        6.5,
        6.5,
        6.5,
        6.5,
        9.25,
        9.25,
        9.25,
        12.0,
        12.0,
        12.0,
        12.0,
        12.0
    };
	double thirdDamage[6]
    {
        0.0,
        0.15,
        0.175,
        0.2,
        0.225,
        0.25
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };
		int buffCount = source->get_buff_count(0x090d4727);
		if (buffCount == 4)
		{
			double val2 = (0.15 + (double)source->get_ap() / 100.0 * 0.06) * ((double)target->get_max_health() - (double)target->get_health());
			if (target->is_minion() && target->is_neutral())
				val2 = std::min(400.0, val2);
			ret.magical = val2;
		}
		else
		{
            double num = firstDamage[std::min(source->get_level(), 18)];
            if (buffCount > 0)
                num += secondDamage[std::min(source->get_level(), 18)] * (double)buffCount;
            ret.magical = num + thirdDamage[std::min(buffCount - 1, 5)] * (double)source->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x090d4727) || source->get_buff_count(0x090d4727) == 4;
	}
};