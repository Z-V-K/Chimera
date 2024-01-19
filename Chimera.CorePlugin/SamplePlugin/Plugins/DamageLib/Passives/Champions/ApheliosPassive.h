#pragma once
#include "../DamagePassive.h"

struct ApheliosPassive : DamagePassive
{
	ApheliosPassive() : DamagePassive(CharacterHash::Aphelios) { }

    double damages[21]
    {
        0.0,
        0.15,
        0.285,
        0.405,
        0.51,
        0.6,
        0.675,
        0.735,
        0.785,
        0.385,
        0.885,
        0.935,
        0.985,
        1.035,
        1.085,
        1.135,
        1.185,
        1.235,
        1.285,
        1.335,
        1.385
    };

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        DamageOutput ret{ 0.0, 0.0, 0.0 };

		if (source->has_buff(0x37eb7de4))
		{
            const int buffCount = source->get_buff_count(0x37eb7de4);
            const double damage = (1.0 + damages[std::min(buffCount, 20)]) * (double) source->get_total_ad();

            ret.physical += damage;
		}

        Buff* targetDebuff = target->get_buff(0x9f57b629);

        if (targetDebuff && targetDebuff->get_caster() == source)
        {
            ret.physical += 15.0 + 0.2 * (double) source->get_bonus_ad();
        }

        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x9f57b629) || source->has_buff(0x37eb7de4);
	}
};