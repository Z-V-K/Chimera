#pragma once
#include "../DamagePassive.h"

struct XinZhaoPassive : DamagePassive
{
	XinZhaoPassive() : DamagePassive(CharacterHash::XinZhao) { }

	double damages[5]
	{
		16.0,
		25.0,
		34.0,
		43.0,
		52.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (source->get_buff_count(0x5bde74ea) == 3)
		{
			ret.physical += source->get_level() < 16 ? (source->get_level() >= 11 ? 0.45 : (source->get_level() >= 6 ? 0.3 : 0.15)) * (double)source->get_total_ad() : 0.6;
		}

		if (source->has_buff(0x4068f075))
		{
			const auto spell = source->get_spell(SlotId::Q);

			if (spell && spell->get_level() > 0)
				ret.physical += damages[std::min(spell->get_level() - 1, 4)] + 0.4 * (double)source->get_bonus_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0x5bde74ea) == 3 || source->has_buff(0x4068f075);
	}
};