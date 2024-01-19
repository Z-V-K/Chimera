#pragma once

#include "../Impl/Common/Common.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
	virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class SpellDataScript final
{
public:
	const std::string& get_name();
	uint32_t get_hash();

	EXPORT_FUNC(const std::string&, get_name, (SpellDataScript* obj), ());
	EXPORT_FUNC(uint32_t, get_hash, (SpellDataScript* obj), ());
};

#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif