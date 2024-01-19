#pragma once
#include "../DamagePassive.h"

struct VaynePassive : DamagePassive
{
	VaynePassive() : DamagePassive(CharacterHash::Vayne) { }

	double damages[5]
	{
		0.75,
		0.85,
		0.95,
		1.05,
		1.15
	};

	double damages1[5]
	{
		50.0,
		65.0,
		80.0,
		95.0,
		110.0
	};

	double damagePercents[5]
	{
		0.06,
		0.07,
		0.08,
		0.9,
		0.1
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (source->has_buff(0xbb89ea44))
		{
			const auto spell = source->get_spell(SlotId::Q);
			if (spell && spell->get_level() > 0)
				ret.physical += damages[std::min(spell->get_level() - 1, 4)] * (double)source->get_total_ad() + 0.5 * (double)source->get_ap();
		}

		if (target->get_buff_count(0x4baefccc) == 2)
		{
			const auto spell = source->get_spell(SlotId::W);

			if (!spell || spell->get_level() == 0)
				return ret;

			double damage = damages1[std::min(spell->get_level() - 1, 4)];
			double val2 = std::max(damagePercents[std::min(spell->get_level() - 1, 4)] * (double)target->get_max_health(), damage);
			if (target->is_minion() && target->is_neutral())
				val2 = std::min(200.0, val2);

			ret.raw += val2;
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xbb89ea44) || target->get_buff_count(0x4baefccc) == 2;
	}
};