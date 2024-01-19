#pragma once
#include "../DamagePassive.h"

struct RivenPassive : DamagePassive
{
	RivenPassive() : DamagePassive(CharacterHash::Riven) { }

	DamageOutput get_damage(GameObject* source, GameObject* target) override
	{
		double totalAttackDamage = (double)source->get_total_ad();
		double level = source->get_level();
		double damage = level < 18 ? (level < 15 ? (level < 12 ? (level < 9 ? (level < 6 ? totalAttackDamage * 0.3 : totalAttackDamage * 0.6) : totalAttackDamage * 0.42) : totalAttackDamage * 0.48) : totalAttackDamage * 0.54) : totalAttackDamage * 0.6;

		return { 0.0, damage, 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->has_buff(0x73bdb94f);
	}
};