#include "../pch.h"
#include "ItemSlot.h"

ItemInfo* ItemSlot::get_item_info() const
{
	ItemInfo** item_info = RVA_CAST_THIS_REF(ItemInfo**, Structures::ItemSlot::ItemInfo);

	if (!item_info)
		return nullptr;

	return *item_info;
}

int16_t ItemSlot::get_stacks() const
{
	const auto info = get_item_info();
	if (!info)
		return 0;

	return info->get_stacks();
}

float ItemSlot::get_price() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	return info->get_price();
}

Enums::ItemId ItemSlot::get_item_id() const
{
	const auto info = get_item_info();
	if (!info)
		return Enums::ItemId::Unknown;

	const auto data = info->get_item_data();
	if (!data)
		return Enums::ItemId::Unknown;

	return data->get_item_id();
}

float ItemSlot::get_ability_haste() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_ability_haste();
}

float ItemSlot::get_health() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_health();
}

float ItemSlot::get_movement_speed() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_movement_speed();
}

float ItemSlot::get_armor() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_armor();
}

float ItemSlot::get_magic_resistance() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_magic_resistance();
}

float ItemSlot::get_ad() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_ad();
}

float ItemSlot::get_ap() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_ap();
}

float ItemSlot::get_attack_speed_multiplier() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_attack_speed_multiplier();
}

float ItemSlot::get_shield_power_multiplier() const
{
	const auto info = get_item_info();
	if (!info)
		return 0.f;

	const auto data = info->get_item_data();
	if (!data)
		return 0.f;

	return data->get_shield_power_multiplier();
}

ItemTexture ItemSlot::get_texture() const
{
	const auto info = get_item_info();
	if (!info)
		return { };

	const auto data = info->get_item_data();
	if (!data)
		return { };

	const auto tex = data->get_texture();

	if (!tex)
		return { };

	return { tex->get_dx_texture(), tex->get_uv() };
}