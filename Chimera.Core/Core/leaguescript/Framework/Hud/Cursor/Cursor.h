#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif
class Cursor final
{
public:
	const Vec3& get_world_position();
	const Vec3& get_last_click_position();
	GameObject* get_hovered_unit();
	unsigned get_hovered_unit_id();

	EXPORT_FUNC(const Vec3&, get_world_position, (Cursor* obj), ());
	EXPORT_FUNC(const Vec3&, get_last_click_position, (Cursor* obj), ());
	EXPORT_FUNC(GameObject*, get_hovered_unit, (Cursor* obj), ());
};
#undef EXPORT_FUNC