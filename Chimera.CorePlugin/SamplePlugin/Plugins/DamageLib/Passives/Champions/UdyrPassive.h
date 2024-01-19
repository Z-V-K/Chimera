#pragma once
#include "../DamagePassive.h"

struct UdyrPassive : DamagePassive
{
	UdyrPassive() : DamagePassive(CharacterHash::Udyr) { }

	double damages[6]
	{
		5.0,
		11.0,
		17.0,
		23.0,
		29.0,
		35.0
	};

	double damages2[18]
	{
		0.015,
		0.0159,
		0.0168,
		11.0 / 625.0,
		0.0185,
		0.0194,
		0.0203,
		0.0212,
		0.0221,
		0.0229,
		0.0238,
		0.0247,
		16.0 / 625.0,
		0.0265,
		0.0274,
		0.0282,
		0.0291,
		0.03
	};

	double damages3[6]
	{
		0.03,
		0.042,
		0.054,
		0.066,
		0.078,
		0.09
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (source->get_buff_count(0x294e7b72) > 0)
		{
			const auto spell = source->get_spell(SlotId::Q);

			if (spell && spell->get_level() > 0)
				ret.physical += damages[std::min(spell->get_level() - 1, 5)] + 0.25 * (double)source->get_bonus_ad();
		}

		if (source->has_buff(0xb963c700))
			ret.magical += (damages2[std::min(source->get_level() - 1, 17)] + 0.006 * ((double)source->get_ap() / 100.0)) * (double)target->get_max_health();

		if (source->has_buff(0x6abe7702))
		{
			const auto spell = source->get_spell(SlotId::Q);

			if (spell && spell->get_level() > 0)
				ret.magical += (damages3[std::min(spell->get_level() - 1, 5)] + 0.01 * (double)source->get_bonus_ad() * 0.04) * (double)target->get_max_health();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0x294e7b72) > 0 || source->has_buff(0xb963c700) || source->has_buff(0x6abe7702);
	}
};