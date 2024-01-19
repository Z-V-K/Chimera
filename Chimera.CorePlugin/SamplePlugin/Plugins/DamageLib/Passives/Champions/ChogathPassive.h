#pragma once
#include "../DamagePassive.h"

struct ChogathPassive : DamagePassive
{
	ChogathPassive() : DamagePassive(CharacterHash::Chogath) { }

	double damages[5]
	{
		22.0,
		34.0,
		46.0,
		58.0,
		70.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::E);
		if (!spell || spell->get_level() == 0)
			return { 0.0, 0.0, 0.0 };

		auto feastCount = source->get_buff_count(0x8682fc00);

		double damage = damages[std::min(spell->get_level() - 1, 4)] + 0.3 * (double)source->get_ap() + (0.03 + (feastCount > 0 ? feastCount * 0.05 : 0.0)) * (double)target->get_max_health();

		return { damage, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xb49346ca);
	}
};