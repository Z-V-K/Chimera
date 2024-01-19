#pragma once
#include "../DamagePassive.h"

struct IllaoiPassive : DamagePassive
{
	IllaoiPassive() : DamagePassive(CharacterHash::Illaoi) { }

	double damages[5]
	{
		0.03,
		0.035,
		0.04,
		0.045,
		0.05
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, (damages[std::min(source->get_spell(SlotId::W)->get_level()  - 1, 4)] + 0.04 * (double)source->get_total_ad() / 100.0) * (double)target->get_max_health(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xb9069cbc);
	}
};