#pragma once
#include "../DamagePassive.h"

struct KaylePassive : DamagePassive
{
	KaylePassive() : DamagePassive(CharacterHash::Kayle) { }

	double damages[5]
	{
		15.0,
		20.0,
		25.0,
		30.0,
		35.0
	};

	double damagePercents[5]
	{
		 0.08,
		  0.1,
		  0.12,
		  0.14,
		  0.16
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (source->get_level() >= 16 || (source->get_level() >= 11 && source->get_buff_count(0xbe6f5dc3) == 5))
			ret.magical = -10.0 * (double)(source->get_level() - 1) * 3.0 + 0.1 * (double) source->get_bonus_ad() + 0.2 * (double)source->get_ap();

		if (source->has_buff(0x6280f79a))
		{
			auto spell = source->get_spell(SlotId::E);
			ret.magical += damages[std::min(spell->get_level() - 1, 4)] + 0.1 * (double)source->get_total_ad() + 0.2 * (double)source->get_ap() + damagePercents[std::min(spell->get_level() - 1, 4)] + ((double)source->get_ap() / 100.0) * ((double)target->get_max_health() - (double)target->get_health());
		}
		
		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		if (source->get_level() >= 16 || source->has_buff(0x6280f79a))
			return true;

		if (source->get_level() >= 11 && source->get_buff_count(0xbe6f5dc3) == 5)
			return true;

		return false;
	}
};