#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct AshePassive : DamagePassive
{
	AshePassive() : DamagePassive(CharacterHash::Ashe) { }

	double damages[5]
	{
		0.05,
		0.1,
		0.115,
		0.2,
		0.25
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		if (target->has_buff(0x3639871a))
		{
			ret.physical += (0.1 + (double)source->get_crit() / 100.0 * (double)DamageLib::get_crit_mulitplier(source)) * (double)source->get_total_ad();
		}

		if (source->has_buff(0xd05b60b5))
		{
			auto qSpell = source->get_spell(SlotId::Q);

			if (qSpell && qSpell->get_level() > 0)
				ret.physical += damages[std::min(qSpell->get_level() - 1, 4)] * (double)source->get_total_ad();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return target->has_buff(0x3639871a) || source->has_buff(0xd05b60b5);
	}
};