#pragma once
#include "../DamagePassive.h"

struct BardPassive : DamagePassive
{
	BardPassive() : DamagePassive(CharacterHash::Bard) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::Auto1);
		if (spell && spell->get_ammo() > 0)
			return { (double)(35 + 14 * (spell->get_ammo() / 5)) + 0.3 * (double)source->get_ap(), 0.0, 0.0 };

		return { };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0x669670d4) > 0;
	}
};