#pragma once
#include "../DamagePassive.h"

struct RenataPassive : DamagePassive
{
	RenataPassive() : DamagePassive(CharacterHash::Renata) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return {  (0.01 + 1.0 / 400.0 * (double)std::min(source->get_level() - 1, 17) + 0.01 * (double)source->get_total_ad() / 100.0) * (double)target->get_max_health(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x4b35af95);
	}
};