#pragma once
#include "../DamagePassive.h"

struct FizzPassive : DamagePassive
{
	FizzPassive() : DamagePassive(CharacterHash::Fizz) { }

	double damages[5]
	{
		50.0,
		70.0,
		90.0,
		110.0,
		130.0
	};

	double damages2[5]
	{
		10.0,
		15.0,
		20.0,
		25.0,
		30.0
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		if (source->has_buff(0xac511301))
		{
			auto spell = source->get_spell(SlotId::W);

			if (spell && spell->get_level() > 0)
			{
				ret.magical += damages[std::min(spell->get_level() - 1, 4)] + 0.5 * (double)source->get_ap();
			}
		}

		if (auto buff = target->get_buff(0x944b356f))
		{
			if (buff->get_caster() == source)
			{
				auto spell = source->get_spell(SlotId::W);

				if (spell && spell->get_level() > 0)
				{
					ret.magical += damages2[std::min(spell->get_level() - 1, 4)] + .35 * source->get_ap();
				}
			}
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0xac511301) || target->has_buff(0x944b356f);
	}
};