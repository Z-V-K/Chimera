#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Spells/SpellData/SpellData.h"
#include "../Framework/Enums/SpellEnums.h"
#include "../Impl/Vector/Vector.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
	virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class GameObject;

class SpellCastInfo final
{
public:
	unsigned get_src_index() const;
	unsigned get_target_index() const;
	SpellData* get_spell_data() const;
	const Vec3& get_start_pos() const;
	const Vec3& get_end_pos() const;
	const Vec3& get_cast_pos() const;
	bool is_auto() const;
	bool is_spell() const;
	bool is_special_attack() const;
	Enums::SpellSlot get_slot() const;
	GameObject* get_source() const;
	GameObject* get_target() const;
	float get_cast_delay() const;

	EXPORT_FUNC(GameObject*, get_source, (SpellCastInfo* obj), ());
	EXPORT_FUNC(GameObject*, get_target, (SpellCastInfo* obj), ());
	EXPORT_FUNC(SpellData*, get_spell_data, (SpellCastInfo* obj), ());
	EXPORT_FUNC(const Vec3&, get_start_pos, (SpellCastInfo* obj), ());
	EXPORT_FUNC(const Vec3&, get_end_pos, (SpellCastInfo* obj), ());
	EXPORT_FUNC(const Vec3&, get_cast_pos, (SpellCastInfo* obj), ());
	EXPORT_FUNC(bool, is_auto, (SpellCastInfo* obj), ());
	EXPORT_FUNC(bool, is_spell, (SpellCastInfo* obj), ());
	EXPORT_FUNC(bool, is_special_attack, (SpellCastInfo* obj), ());
	EXPORT_FUNC(Enums::SpellSlot, get_slot, (SpellCastInfo* obj), ());
	EXPORT_FUNC(float, get_cast_delay, (SpellCastInfo* obj), ());
};

#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif