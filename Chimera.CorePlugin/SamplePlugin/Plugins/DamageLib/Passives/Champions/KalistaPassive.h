#pragma once
#include "../DamagePassive.h"

struct KalistaPassive : DamagePassive
{
	KalistaPassive() : DamagePassive(CharacterHash::Kalista) { }

	double damages[5]
	{
		0.14,
		0.15,
		0.16,
		0.17,
		0.18
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
		return target->has_buff(0xbe5519a3);
	}
};