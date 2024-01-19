#pragma once
#include "../DamagePassive.h"

struct AkaliPassive : DamagePassive
{
	AkaliPassive() : DamagePassive(CharacterHash::Akali) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		const double val = source->get_level() == 1 ? 35.0 : (double)(35 + 147 / (17 * (source->get_level() - 1)));
		return { val, 0.0, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x553ccb5d);
	}
};