#pragma once
#include "../DamagePassive.h"

struct SylasPassive : DamagePassive
{
	SylasPassive() : DamagePassive(CharacterHash::Sylas) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 1.2999999523162842 * source->get_total_ad() + .25 * source->get_ap(), 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x87b90a98);
	}
};