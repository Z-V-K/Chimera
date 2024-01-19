#pragma once
#include "../DamagePassive.h"

struct ThreshPassive : DamagePassive
{
	ThreshPassive() : DamagePassive(CharacterHash::Thresh) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const auto spell = source->get_spell(SlotId::E);

		if (!spell || spell->get_level() == 0)
			return { };

		double damage = source->get_buff_count(0x5fbfbf13) * 1.5 + (.5 + 0.30000001192092896 * spell->get_level()) * source->get_total_ad();

		if (source->has_buff(0x13deae50))
			damage *= .7;
		if (source->has_buff(0x14deafe3))
			damage *= .4;
		if (source->has_buff(0x15deb176))
			damage *= .1;

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xa7e7b4b8);
	}
};