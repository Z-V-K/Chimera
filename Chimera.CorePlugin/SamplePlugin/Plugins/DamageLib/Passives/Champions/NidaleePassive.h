#pragma once
#include "../DamagePassive.h"

struct NidaleePassive : DamagePassive
{
	NidaleePassive() : DamagePassive(CharacterHash::Nidalee) { }

	double damages[5]
	{
		5.0,
		30.0,
		55.0,
		80.0
	};

	double passiveDamages[5]
	{
		7.0,
		42.0,
		77.0,
		112.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::R);

		if (spell->get_level() == 0)
			return { };

		double damage = damages[std::min(spell->get_level() - 1, 3)] + 0.75 * (double)source->get_total_ad() + 0.4 * (double)source->get_ap();
		if (target->has_buff(0xf27ace98))
			damage = passiveDamages[std::min(spell->get_level() - 1, 3)] + 1.05 * (double)source->get_total_ad() + 0.56 * (double)source->get_ap();

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xccd4c05e);
	}
};