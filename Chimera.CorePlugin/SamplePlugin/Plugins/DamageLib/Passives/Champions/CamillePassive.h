#pragma once
#include "../DamagePassive.h"

struct CamillePassive : DamagePassive
{
	CamillePassive() : DamagePassive(CharacterHash::Camille) { }

	double damages[5]
	{
		0.2,
		0.25,
		0.3,
		0.35,
		0.4
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };

		auto spell = source->get_spell(SlotId::Q);

		if (!spell || spell->get_level() == 0)
			return ret;

		if (source->has_buff(0x2b5c686d))
		{
			ret.physical += 1.0 - std::min(1.0, 0.36 + 0.04 * (double)(source->get_level() - 1)) * 2.0 * damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad();
			ret.raw += std::min(1.0, 0.36 + 0.04 * (double)(source->get_level() - 1) * 2.0 * damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad());
		}

		if (source->has_buff(0x001c2dcd))
		{
			ret.physical += damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x2b5c686d) || source->has_buff(0x001c2dcd);
	}
};