#pragma once
#include "../DamagePassive.h"

struct KennenPassive : DamagePassive
{
	KennenPassive() : DamagePassive(CharacterHash::Kennen) { }

	double damages[5]
	{
		35.0,
		45.0,
		55.0,
		65.0,
		75.0
	};

	double damagePercents[5]
	{
		0.8,
		0.9,
		1.0,
		1.1,
		1.2
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::W);

		const auto val = damages[std::min(spell->get_level() - 1, 4)] + damagePercents[std::min(spell->get_level() - 1, 4)] * (double)source->get_bonus_ad() + 0.35 * (double)source->get_ap();

		return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x880cea47);
	}
};