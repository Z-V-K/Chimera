#include "../pch.h"
#include "ItemData.h"
#include "../Framework/Rendering/r3dTexture/r3dTexture.h"

Enums::ItemId ItemData::get_item_id()
{
	return RVA_CAST_THIS(Enums::ItemId, Structures::ItemData::ItemId);
}

float ItemData::get_ability_haste()
{
	return RVA_CAST_THIS(float, Structures::ItemData::AbilityHaste);
}

float ItemData::get_health()
{
	return RVA_CAST_THIS(float, Structures::ItemData::Health);
}

float ItemData::get_movement_speed()
{
	return RVA_CAST_THIS(float, Structures::ItemData::MovementSpeed);
}

float ItemData::get_armor()
{
	return RVA_CAST_THIS(float, Structures::ItemData::Armor);
}

float ItemData::get_magic_resistance()
{
	return RVA_CAST_THIS(float, Structures::ItemData::MagicResistance);
}

float ItemData::get_ad()
{
	return RVA_CAST_THIS(float, Structures::ItemData::Ad);
}

float ItemData::get_ap()
{
	return RVA_CAST_THIS(float, Structures::ItemData::Ap);
}

float ItemData::get_attack_speed_multiplier()
{
	return RVA_CAST_THIS(float, Structures::ItemData::AttackSpeedMultiplier);
}

float ItemData::get_shield_power_multiplier()
{
	return RVA_CAST_THIS(float, Structures::ItemData::ShieldPowerMultiplier);
}

r3dTexture* ItemData::get_texture()
{
	return RVA_CAST_THIS(r3dTexture*, Structures::ItemData::Texture);
}