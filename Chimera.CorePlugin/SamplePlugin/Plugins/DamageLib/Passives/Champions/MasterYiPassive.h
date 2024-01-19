#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct MasterYiPassive : DamagePassive
{
	MasterYiPassive() : DamagePassive(CharacterHash::MasterYi) { }

	double damages[5]
	{
		30.0,
		35.0,
		40.0,
		45.0,
		50.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (source->has_buff(0xdb51d502))
		{
			ret.physical = 0.5 * (double)source->get_total_ad() * (double)DamageLib::get_crit_mulitplier(source);
		}

		if (source->has_buff(0x40dc9ce4))
		{
			const auto spell = source->get_spell(SlotId::E);

			ret.raw = damages[std::min(spell->get_level() - 1, 4)] + 0.3 * (double)source->get_bonus_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xdb51d502) || source->has_buff(0x40dc9ce4);
	}
};