#pragma once
#include "../DamagePassive.h"

struct GwenPassive : DamagePassive
{
	GwenPassive() : DamagePassive(CharacterHash::Gwen) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

        float val2 = (float)(0.0099999997764825821 + (double)source->get_ap() / 100.0 * 0.00800000037997961) * target->get_max_health();
        if (target->is_hero())
            return { val2, 0.0, 0.0 };
        
        if (target->is_minion())
        {
            if (target->is_neutral())
                return { std::min((float)(10.0 + 0.25 * (double)source->get_ap()), val2), 0.0, 0.0 };

            return { (double)target->get_health_percent() >= 40.0 ? (double)val2 : (double)val2 + 8.0 + (source->get_level() > 1 ? 22.0 / (17.0 * ((double)source->get_level() - 1.0)) : 0.0), 0.0, 0.0 };
        }
        return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};