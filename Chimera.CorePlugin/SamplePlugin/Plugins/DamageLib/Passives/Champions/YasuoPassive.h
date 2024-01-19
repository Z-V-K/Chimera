#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct YasuoPassive : DamagePassive
{
	YasuoPassive() : DamagePassive(CharacterHash::Yasuo) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, 0.9 * (double)DamageLib::get_crit_mulitplier(source) * (double)source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return abs(source->get_crit() - 1.f) < 1.4012984643248171E-45;
	}
};