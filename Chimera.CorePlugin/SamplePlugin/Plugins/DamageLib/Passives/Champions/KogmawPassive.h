#pragma once
#include "../DamagePassive.h"

struct KogmawPassive : DamagePassive
{
	KogmawPassive() : DamagePassive(CharacterHash::KogMaw) { }

	double damages[5]
	{
		0.035,
		17.0 / 400.0,
		0.05,
		23.0 / 400.0,
		0.065
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };
		const auto spell = source->get_spell(SlotId::W);

		if (spell->get_ammo() == 1)
			ret.magical = damages[std::min(spell->get_level() - 1, 4)] + 0.01 * (double)(source->get_ap() / 100.0)* (double)target->get_max_health();

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xf12c3953);
	}
};