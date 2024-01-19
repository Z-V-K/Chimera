#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct JinxPassive : DamagePassive
{
	JinxPassive() : DamagePassive(CharacterHash::Jinx) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Q);

		if (!spell || spell->get_level() < 0)
			return { };

		return { 0.0,0.1 * (double)source->get_total_ad() * (double)DamageLib::get_crit_mulitplier(source), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xd2a0ed81);
	}
};