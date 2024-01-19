#pragma once
#include "../../DamageLib.h"
#include "../DamagePassive.h"

struct GalioPassive : DamagePassive
{
	GalioPassive() : DamagePassive(CharacterHash::Galio) { overwrite_attack_damage = [](GameObject* obj){ return obj->get_spell(SlotId::W)->get_level() > 0; }; }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		DamageOutput ret{ 0.0, 0.0, 0.0 };
		if (source->get_spell(SlotId::W)->get_level() > 0)
		{
			if (!source->has_buff(0x9c13438d))
				ret.physical += source->get_total_ad();
		}

		if (source->has_buff(0x9c13438d))
		{
			float num = (float)(4.1180000305175781 + 10.881999969482422 * (double)source->get_level() + (double)source->get_total_ad() + (double)source->get_ap() * 0.5 + (double)source->get_spell_block() * 0.60000002384185791);
			ret.magical += (double)abs(source->get_crit() - 1.f) < 1.4012984643248171E-45 ? 4.1180000305175781 + 10.881999969482422 * (double)source->get_level() + (double)source->get_total_ad() * (double)DamageLib::get_crit_mulitplier(source) + (double)source->get_ap() * 0.5 + (double)source->get_bonus_spell_block() * 0.60000002384185791 : (double)num;
		}

		return ret;
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_spell(SlotId::W)->get_level() > 0 || source->has_buff(0x9c13438d);
	}
};