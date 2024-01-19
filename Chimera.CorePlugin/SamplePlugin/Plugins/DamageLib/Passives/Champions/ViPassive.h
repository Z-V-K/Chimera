#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct ViPassive : DamagePassive
{
	ViPassive() : DamagePassive(CharacterHash::Vi) { }

	double damages[5]
	{
		0.04,
		0.055,
		0.07,
		0.085,
		0.1
	};

	double eDamages[5]
	{
		0.0,
		15.0,
		30.0,
		45.0,
		60.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret;

		if (target->get_buff_count(0x3fb02651) == 2)
		{
			const auto spell = source->get_spell(SlotId::W);

			if (spell && spell->get_level() > 0)
			{
				double val2 = (damages[std::min(spell->get_level() - 1, 4)] + 0.01 * (double)source->get_bonus_ad() / 35.0) * (double)target->get_max_health();
				if (target->is_minion() && target->is_neutral())
					val2 = std::max(300.0, val2);

				ret.physical += val2;
			}
		}

		if (source->has_buff(0x6d12325f))
		{
			const auto spell = source->get_spell(SlotId::E);

			if (spell && spell->get_level() > 0)
				ret.physical += (eDamages[spell->get_level() - 1] + 1.2 * (double)source->get_total_ad() + 1.0 * (double)source->get_ap()) * (double)DamageLib::get_crit_mulitplier(source);
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->get_buff_count(0x3fb02651) == 2 || source->has_buff(0x6d12325f);
	}
};