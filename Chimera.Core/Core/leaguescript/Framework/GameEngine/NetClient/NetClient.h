#pragma once

#include "../Impl/Common/Common.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class NetClient final
{
public:
	static NetClient* get_instance();

	int get_ping();

	EXPORT_FUNC(int, get_ping, (NetClient* obj), ());
};

#undef EXPORT_FUNC