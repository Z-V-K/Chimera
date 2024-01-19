#pragma once

#include "../../../SDK/LUA/LuaTexture.h"
#include "../Impl/Common/Common.h"
#include "../Framework/Spells/SpellData/SpellData.h"
#include "../Framework/Enums/SpellEnums.h"
#include "../Framework/Spells/SpellTargetClient/SpellTargetClient.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class SpellSlot final
{
public:
	SpellTargetClient* get_target_client() const;
	SpellData* get_spell_data() const;
	Enums::SpellSlot get_slot_id() const;
	int get_ammo() const;
	float get_max_cooldown() const;
	int get_level() const;
	float get_ready_at() const;
	float get_damage() const;
    float get_cooldown() const;
	float get_ammo_ready_at() const;
	float get_ammo_cooldown() const;
	PVOID get_icon() const;
	LuaTexture get_icon_lua() const;

	EXPORT_FUNC(SpellData*, get_spell_data, (SpellSlot* obj), ());
	EXPORT_FUNC(Enums::SpellSlot, get_slot_id, (SpellSlot* obj), ());
	EXPORT_FUNC(int, get_ammo, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_max_cooldown, (SpellSlot* obj), ());
	EXPORT_FUNC(int, get_level, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_ready_at, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_damage, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_cooldown, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_ammo_ready_at, (SpellSlot* obj), ());
	EXPORT_FUNC(float, get_ammo_cooldown, (SpellSlot* obj), ());
	EXPORT_FUNC(PVOID, get_icon, (SpellSlot* obj), ());
};
#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif