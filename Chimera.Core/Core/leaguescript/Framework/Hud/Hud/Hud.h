#pragma once

#include "../Impl/Common/Common.h"
#include "../Framework/Hud/Cursor/Cursor.h"

#include "../Framework/Enums/WindowFocusEnum.h"
#include "../Framework/Hud/Minimap/Minimap.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif
class Hud final
{
public:
	static Hud* get_instance();
	Cursor* get_cursor();
	Enums::WindowFocus get_window_focus();

	bool is_window_focused();

	EXPORT_FUNC(bool, is_window_focused, (Hud* obj), ());
};
#undef EXPORT_FUNC
