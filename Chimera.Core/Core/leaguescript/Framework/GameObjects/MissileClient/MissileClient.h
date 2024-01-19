#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"
#include "../Framework/Enums/SpellEnums.h"
#include "../Framework/Spells/SpellData/SpellData.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class GameObject;

class MissileClient final
{
public:
	SpellData* get_spell_data() const;
	std::string get_caster_name() const;
	const Vec3& get_start_position() const;
	const Vec3& get_end_position() const;
	const Vec3& get_cast_position() const;
	Enums::SpellSlot get_slot() const;
	unsigned get_missile_index() const;
	unsigned get_caster_index() const;
	unsigned get_target_index() const;

	GameObject* get_source() const;
	GameObject* get_target() const;

	EXPORT_FUNC(SpellData*, get_spell_data, (MissileClient* obj), ());
	EXPORT_FUNC(const Vec3&, get_start_position, (MissileClient* obj), ());
	EXPORT_FUNC(const Vec3&, get_end_position, (MissileClient* obj), ());
	EXPORT_FUNC(const Vec3&, get_cast_position, (MissileClient* obj), ());
	EXPORT_FUNC(Enums::SpellSlot, get_slot, (MissileClient* obj), ());
	EXPORT_FUNC(unsigned, get_missile_index, (MissileClient* obj), ());
	EXPORT_FUNC(GameObject*, get_source, (MissileClient* obj), ());
	EXPORT_FUNC(GameObject*, get_target, (MissileClient* obj), ());
};
#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif