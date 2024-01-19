#pragma once
#include "../DamagePassive.h"

struct GarenPassive : DamagePassive
{
	GarenPassive() : DamagePassive(CharacterHash::Gangplank) { }

	double damages[5]
	{
		30.0,
		60.0,
		90.0,
		120.0,
		150.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (source->has_buff(0x0229b651))
		{
			ret.physical += damages[std::min(source->get_spell(SlotId::Q)->get_level() - 1, 4)] + 0.5 * (double)source->get_total_ad();
		}

		if (auto buff = target->get_buff(0x273cb3b0))
		{
			if (buff->get_caster() == source)
				ret.raw += .01 * target->get_max_health();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x0229b651) || target->has_buff(0x273cb3b0);
	}
};