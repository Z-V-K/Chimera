#pragma once

#include "../../Rendering/r3dTexture/r3dTexture.h"
#include "../Impl/Common/Common.h"
#include "../Framework/Enums/ItemId.h"

class ItemData final
{
public:
	Enums::ItemId get_item_id();
	float get_ability_haste();
	float get_health();
	float get_movement_speed();
	float get_armor();
	float get_magic_resistance();
	float get_ad();
	float get_ap();
	float get_attack_speed_multiplier();
	float get_shield_power_multiplier();
	r3dTexture* get_texture();
};