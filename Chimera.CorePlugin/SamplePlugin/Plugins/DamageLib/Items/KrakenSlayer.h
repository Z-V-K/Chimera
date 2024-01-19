#pragma once
#include "DamageItem.h"

struct KrakenSlayer : DamageItem
{
	KrakenSlayer() : DamageItem(ItemId::Kraken_Slayer, DamageType::Physical) { }

	double damages[18]
	{
		35,
		35,
		35,
		35,
		35,
		35,
		35,
		35,
		40,
		45,
		50,
		55,
		60,
		65,
		70,
		75,
		80,
		85
	};

	DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
	{
		return DamageOutput{ 0.0, damages[std::min(source->get_level() - 1, 17)] + .65 * source->get_total_ad() + .6 * source->get_ap(), 0.0 };
	}

	bool is_active(GameObject* source, GameObject* target) override
	{
		return source->get_buff_count(0xef29d57d) == 2;
	}
};