#pragma once
#include "../DamagePassive.h"

struct BlitzcrankPassive : DamagePassive
{
	BlitzcrankPassive() : DamagePassive(CharacterHash::Blitzcrank) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		if (source->has_buff(0x8f6f81b4))
			ret.physical += 0.75 * (double)source->get_total_ad() + 0.25 * (double)source->get_ap();
		if (source->has_buff(0x80f93835))
		{
			double damage = (double)target->get_max_health() * 0.01;
			if (target->is_minion())
				damage += (double)(60 + 7 * (source->get_level() - 1));
			ret.magical += damage;
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x8f6f81b4) || source->has_buff(0x80f93835);
	}
};