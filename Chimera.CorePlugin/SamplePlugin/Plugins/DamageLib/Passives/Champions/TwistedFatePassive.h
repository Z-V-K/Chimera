#pragma once
#include "../DamagePassive.h"

struct TwistedFatePassive : DamagePassive
{
	TwistedFatePassive() : DamagePassive(CharacterHash::TwistedFate) { }

	double bluedamages[5]
	{
		40.0,
		60.0,
		80.0,
		100.0,
		120.0
	};

	double reddamages[5]
	{
		30.0,
		45.0,
		60.0,
		75.0,
		90.0
	};

	double golddamages[5]
	{
		15.0,
		22.5,
		30.0,
		37.5,
		45.0
	};

	double eDamages[5]
	{
		65.0,
		90.0,
		115.0,
		140.0,
		165.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		const auto espell = source->get_spell(SlotId::W);
		if (espell && espell->get_level() > 0)
		{
			if (source->has_buff(0x8b0b9a1c))
				ret.magical += bluedamages[std::min(espell->get_level() - 1, 4)] + .9 * source->get_ap();
			if (source->has_buff(0x854c3bc3))
				ret.magical += reddamages[std::min(espell->get_level() - 1, 4)] + .6 * source->get_ap();
			if (source->has_buff(0xa96339f2))
				ret.magical += golddamages[std::min(espell->get_level() - 1, 4)] + .5 * source->get_ap();
		}

		if (source->has_buff(0x4aed0ce1))
		{
			const auto spell = source->get_spell(SlotId::E);
			if (spell && spell->get_level() > 0)
				ret.magical += eDamages[std::min(spell->get_level() - 1, 4)] + 0.5 * (double)source->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x4aed0ce1) || source->has_buff(0x8b0b9a1c) || source->has_buff(0x854c3bc3) || source->has_buff(0xa96339f2);
	}
};