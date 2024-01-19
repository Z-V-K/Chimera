#pragma once
#include "../DamagePassive.h"

struct CaitlynPassive : DamagePassive
{
	CaitlynPassive() : DamagePassive(CharacterHash::Caitlyn) { }

    double damages[5]
    {
        40.0,
        85.0,
        130.0,
        175.0,
        220.0
    };
    double damagePercents[5]
    {
        0.40000000596046448,
        0.5,
        0.60000002384185791,
        0.699999988079071,
        0.800000011920929
    };

    bool isWBuffActive(GameObject* source, GameObject* target)
    {
        auto buff = target->get_buff(0x50562405);
        return buff && buff->is_active() && buff->get_caster() && buff->get_caster() == source;
    }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
        DamageOutput ret{ 0.0, 0.0, 0.0 };

        if (source->has_buff(0x7f11477e))
        {
            float num = 1.f;
            float val1 = source->get_crit();
            if (target->is_hero())
                num = source->get_level() < 13 ? (source->get_level() < 7 ? 0.6f : 0.9f) : 1.2f;
            else if (target->is_turret())
                val1 = std::min(val1, 0.4f);
            ret.physical += ((double)num + (double)val1 * 1.2000000476837158 * 1.25) * (double)source->get_total_ad();

            return ret;
        }

        float num1 = 1.f;
        double num2 = 0.0;
        float val1_1 = source->get_crit();
        if (target->is_hero())
        {
            num1 = source->get_level() < 13 ? (source->get_level() < 7 ? 0.6f : 0.85f) : 1.1f;
            if (isWBuffActive(source, target))
            {
                int level = source->get_spell(SlotId::W)->get_level();
                if (level > 0)
                    num2 += damages[std::min(level - 1, 4)] + damagePercents[std::min(level - 1, 4)] * (double)source->get_bonus_ad();
            }
        }
        else if (target->is_turret())
            val1_1 = std::min(val1_1, 0.4f);

        ret.physical += ((double)num1 + (double)val1_1 * 1.25) * (double)source->get_total_ad() + num2;

        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x7f11477e) || isWBuffActive(source, target) || target->has_buff(0x932c853a);
	}
};