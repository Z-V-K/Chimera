#pragma once
#include "../DamagePassive.h"

struct VolibearPassive : DamagePassive
{
	VolibearPassive() : DamagePassive(CharacterHash::Volibear) { }

	double damages[5]
	{
		20.0,
		40.0,
		60.0,
		80.0,
		100.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (source->has_buff(0xa87bcc1a))
		{
			const auto spell = source->get_spell(SlotId::Q);

			if (spell && spell->get_level() > 0)
				ret.physical += damages[std::min(spell->get_level() - 1, 4)] + 1.2000000476837158 * (double)source->get_bonus_ad();
		}

		if (source->has_buff(0xf5ccee7a))
		{
			if (source->get_level() <= 3)
			{
				ret.magical += 10.0 + 1.0 * (double)source->get_level() + 0.40000000596046448 * (double)source->get_ap();
				return ret;
			}
			if (source->get_level() <= 6)
			{
				ret.magical += 10.0 + 2.0 * (double)source->get_level() + 0.40000000596046448 * (double)source->get_ap();
				return ret;
			}

			ret.magical += source->get_level() <= 13 ? 10.0 + 3.0 * (double)source->get_level() + 0.40000000596046448 * (double)source->get_ap() : 10.0 + 4.0 * (double)source->get_level() + 0.40000000596046448 * (double)source->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xa87bcc1a) || source->has_buff(0xf5ccee7a);
	}
};