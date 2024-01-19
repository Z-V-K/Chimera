#pragma once
#include "../DamagePassive.h"

struct RenataMarkPassive : DamagePassive
{
	RenataMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto caster = target->get_buff(0x4b35af95)->get_caster();
		double damage = 0.0;
		if (caster == source)
			damage = (0.01 + 1.0 / 400.0 * (double)std::min(source->get_level() - 1, 17) + 0.01 * (double)source->get_total_ad() / 100.0) * (double)target->get_max_health();

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x4b35af95);
	}
};