#pragma once
#include "../DamagePassive.h"

struct DariusPassive : DamagePassive
{
	DariusPassive() : DamagePassive(CharacterHash::Darius) { }

	double damages[5]
	{
		0.4,
		0.45,
		0.5,
		0.55,
		0.6
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		auto spell = source->get_spell(SlotId::W);

		if (spell && spell->get_level() > 0)
		{
			ret.physical = damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x14359e50);
	}
};