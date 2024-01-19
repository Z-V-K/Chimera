#pragma once
#include "../DamagePassive.h"

struct JhinPassive : DamagePassive
{
	JhinPassive() : DamagePassive(CharacterHash::Jhin) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (source->has_buff(0xac3fa0c8))
			ret.physical += (source->get_level() < 6 ? 0.15 : (source->get_level() < 11 ? 0.2 : 0.25)) * ((double)target->get_max_health() - (double)target->get_health());

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xac3fa0c8);
	}
};