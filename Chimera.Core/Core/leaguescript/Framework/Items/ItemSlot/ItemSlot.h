#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Items/ItemInfo/ItemInfo.h"
#include "../Framework/Enums/ItemId.h"
#include "../Impl/Vector/Vector.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
	virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

struct ItemTexture
{
	PVOID texture;
	Vec4 UV;

	Vec2 get_uv_min();
	Vec2 get_uv_max();
	bool is_valid();
};

class ItemSlot final
{
public:
	ItemInfo* get_item_info() const;
	
	Enums::ItemId	get_item_id() const;
	int16_t			get_stacks() const;

	float			get_price() const;
	float			get_ability_haste() const;
	float			get_health() const;
	float			get_movement_speed() const;
	float			get_armor() const;
	float			get_magic_resistance() const;
	float			get_ad() const;
	float			get_ap() const;
	float			get_attack_speed_multiplier() const;
	float			get_shield_power_multiplier() const;
	ItemTexture		get_texture() const;

	EXPORT_FUNC(int16_t, get_stacks, (ItemSlot* obj), ());
	EXPORT_FUNC(Enums::ItemId, get_item_id, (ItemSlot* obj), ());

	EXPORT_FUNC(float, get_price, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_ability_haste, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_health, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_movement_speed, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_armor, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_magic_resistance, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_ad, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_ap, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_attack_speed_multiplier, (ItemSlot* obj), ());
	EXPORT_FUNC(float, get_shield_power_multiplier, (ItemSlot* obj), ());
	EXPORT_FUNC(ItemTexture, get_texture, (ItemSlot* obj), ());
};
#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif