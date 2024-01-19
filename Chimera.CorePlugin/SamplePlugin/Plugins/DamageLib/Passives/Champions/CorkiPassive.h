#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct CorkiPassive : DamagePassive
{
	CorkiPassive() : DamagePassive(CharacterHash::Corki) { overwrite_attack_damage = [](GameObject* obj){ return true; }; }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };

		double damage = 0.8 * (double)source->get_total_ad();
		if ((double)abs(source->get_crit() - 1.f) < 1.4012984643248171E-45)
			damage = 0.8 * (double)source->get_total_ad() * (double)DamageLib::get_crit_mulitplier(source);

		ret.magical = damage;
		ret.physical = (double)abs(source->get_crit() - 1.f) < 1.4012984643248171E-45 ? 0.2 * (double)DamageLib::get_crit_mulitplier(source) * (double)source->get_total_ad() : 0.2 * (double)source->get_total_ad();

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return true;
	}
};