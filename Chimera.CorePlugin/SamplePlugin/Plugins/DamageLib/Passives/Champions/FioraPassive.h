#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct FioraPassive : DamagePassive
{
	FioraPassive() : DamagePassive(CharacterHash::Fiora) { }

	double damages[5]
	{
		-0.4,
		-0.3,
		-0.2,
		-0.1,
		0.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };

		auto spell = source->get_spell(SlotId::E);

		if (spell && spell->get_level() > 0)
		{
			ret.physical = DamageLib::get_crit_mulitplier(source) + damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x0016a813);
	}
};