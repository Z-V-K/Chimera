#pragma once
#include "../DamagePassive.h"

struct JaycePassive : DamagePassive
{
	JaycePassive() : DamagePassive(CharacterHash::Jayce) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

	double damages[6]
	{
		0.7,
		0.78,
		0.86,
		0.94,
		1.02,
		1.1
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto spell = source->get_spell(SlotId::W);
		return { 0.0, spell && spell->get_level() > 0 ? damages[std::min(spell->get_level() - 1, 5)] * (double)source->get_total_ad() : (double)source->get_total_ad(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x0e95d0e7);
	}
};