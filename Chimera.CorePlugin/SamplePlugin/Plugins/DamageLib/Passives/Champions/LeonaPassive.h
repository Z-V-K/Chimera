#pragma once
#include "../DamagePassive.h"

struct LeonaPassive : DamagePassive
{
	LeonaPassive() : DamagePassive(CharacterHash::Leona) { }

	double damages[5]
	{
		10.0,
		35.0,
		60.0,
		85.0,
		110.0
	};

	double damages2[5]
	{
		30.0,
		40.0,
		50.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (source->has_buff(0x11bc4e4b))
		{
			const auto spell = source->get_spell(SlotId::Q);

			ret.magical = damages[std::min(spell->get_level() - 1, 4)] + 0.3 * (double)source->get_ap();
		}

		if (source->has_buff(0x72286339))
		{
			const auto spell = source->get_spell(SlotId::R);

			ret.magical += damages[std::min(spell->get_level() - 1, 2)] + 0.15 * (double)source->get_ap();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x11bc4e4b) || source->has_buff(0x72286339);
	}
};