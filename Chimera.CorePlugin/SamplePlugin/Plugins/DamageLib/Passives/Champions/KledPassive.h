#pragma once
#include "../DamagePassive.h"

struct KledPassive : DamagePassive
{
	KledPassive() : DamagePassive(CharacterHash::Kled) { overwrite_attack_damage = [](GameObject* obj) { return true; }; }

	double damages[5]
	{
		20.0,
		30.0,
		40.0,
		50.0,
		60.0
	};

	double damagePercents[5]
	{
		0.045,
		0.05,
		0.055,
		0.06,
		0.065
	};

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret { };

		if (source->get_spell(SlotId::Q)->get_spell_data()->get_hash() == 0x90f439f8)
		{
			ret.physical = .8 * source->get_total_ad();
		}

		if (source->has_buff(0x71500c0e))
		{
			const auto spell = source->get_spell(SlotId::W);

			if (spell->get_ammo() == 1)
				ret.physical += damages[std::min(spell->get_level() - 1, 4)] + (damagePercents[std::min(spell->get_level() - 1, 4)] + 0.05 * (double)source->get_bonus_ad() / 100.0) * (double)target->get_max_health();
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x71500c0e);
	}
};