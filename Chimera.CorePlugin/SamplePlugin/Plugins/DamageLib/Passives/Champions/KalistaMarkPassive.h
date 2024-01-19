#pragma once
#include "../DamagePassive.h"

struct KalistaMarkPassive : DamagePassive
{
	KalistaMarkPassive() : DamagePassive(CharacterHash::Unknown) { }

	double damages[5]
	{
		0.05,
		0.075,
		0.1,
		0.125,
		0.15
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		auto buff = target->get_buff(0xbe5519a3);

		if (buff->get_caster() == source)
		{
			auto spell = source->get_spell(SlotId::W);

			if (spell && spell->get_level() > 0)
			{
				double num = damages[std::min(spell->get_level() - 1, 4)] * (double)target->get_max_health();
				return { target->is_minion() && (double)target->get_health() < 125.0 ? (double)target->get_max_health() : num, 0.0, 0.0 };
			}
		}

		return { };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0xbe5519a3) && source->has_buff(0x8a9646fd);
	}
};