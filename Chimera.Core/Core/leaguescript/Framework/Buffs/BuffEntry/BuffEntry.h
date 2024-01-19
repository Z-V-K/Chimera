#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Enums/BuffType.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class GameObject;

class BuffEntry final {
public:

	bool is_valid() const;
	
	int get_count_alt() const;
	int get_count_int() const;
	float get_count_float() const;
	GameObject* get_caster() const;
	GameObject* get_owner() const;

	Enums::BuffType get_type() const;
	float get_start_time() const;
	float get_end_time() const;

	std::string get_name() const;
	uint32_t get_hash() const;
	PVOID get_texture() const;

	int get_count() const;
	float get_remaining_time() const;
	float get_total_duration() const;

	EXPORT_FUNC(Enums::BuffType, get_type, (BuffEntry* obj), ());
	EXPORT_FUNC(int, get_count, (BuffEntry* obj), ());
	EXPORT_FUNC(float, get_start_time, (BuffEntry* obj), ());
	EXPORT_FUNC(float, get_end_time, (BuffEntry* obj), ());
	EXPORT_FUNC(float, get_remaining_time, (BuffEntry* obj), ());
	EXPORT_FUNC(float, get_total_duration, (BuffEntry* obj), ());
	EXPORT_FUNC(std::string, get_name, (BuffEntry* obj), ());
	EXPORT_FUNC(uint32_t, get_hash, (BuffEntry* obj), ());
	EXPORT_FUNC(GameObject*, get_caster, (BuffEntry* obj), ());
	EXPORT_FUNC(GameObject*, get_owner, (BuffEntry* obj), ());
	EXPORT_FUNC(PVOID, get_texture, (BuffEntry* obj), ());
};

#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif