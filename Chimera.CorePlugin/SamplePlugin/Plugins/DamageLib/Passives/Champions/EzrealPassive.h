#pragma once
#include "../DamagePassive.h"

struct EzrealPassive : DamagePassive
{
	EzrealPassive() : DamagePassive(CharacterHash::Ezreal) { }

	double damages[5]
	{
		80.0,
		135.0,
		190.0,
		245.0,
		300.0
	};

	double damagePercents[5]
	{
		0.7,
		0.75,
		0.8,
		0.85,
		0.9
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };

		auto buff = target->get_buff(0xdd330ca6);
		if (buff && buff->get_caster() == source)
		{
			auto spell = source->get_spell(SlotId::W);
			if (spell && spell->get_level() > 0)
				ret.magical += damages[spell->get_level() - 1] + 0.6 * (double)source->get_bonus_ad() + damagePercents[spell->get_level() - 1] * (double)source->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0xdd330ca6);
	}
};