#pragma once
#include "../DamagePassive.h"

struct NautilusPassive : DamagePassive
{
	NautilusPassive() : DamagePassive(CharacterHash::Nautilus) { }

	double damages[5]
	{
		15.0,
		20.0,
		25.0,
		30.0,
		35.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ };
		if (source->has_buff(0x24621017))
		{
			const auto spell = source->get_spell(SlotId::W);

			if (spell->get_level() > 0)
				ret.magical = damages[std::min(spell->get_level() - 1, 4)] + 0.2 * (double)source->get_ap();
		}

		if (!target->has_buff(0x5922a2ff))
		{
			ret.magical += (2 + 6 * source->get_level());
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x24621017) || !target->has_buff(0x5922a2ff);
	}
};