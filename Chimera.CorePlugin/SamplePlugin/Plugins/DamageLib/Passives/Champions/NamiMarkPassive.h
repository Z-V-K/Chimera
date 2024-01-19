#pragma once
#include "../DamagePassive.h"

struct NamiMarkPassive : DamagePassive
{
	NamiMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	double damages[5]
	{
		25.0,
		40.0,
		55.0,
		70.0,
		85.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (const auto buff = source->get_buff(0xe503837d))
		{
			const auto caster = buff->get_caster();

			if (!caster)
				return ret;

			const auto spell = caster->get_spell(SlotId::E);
			ret.magical = damages[std::min(spell->get_level() - 1, 4)] + 0.2 * (double)caster->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xe503837d);
	}
};