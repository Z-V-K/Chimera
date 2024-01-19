#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct UrgotPassive : DamagePassive
{
	UrgotPassive() : DamagePassive(CharacterHash::Urgot) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		return { 0.0, source->get_total_ad() * ((double)DamageLib::get_crit_mulitplier(source) - 1.0) , 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_spell(SlotId::W)->get_spell_data()->get_hash() == 0x0be0ffcb;
	}
};