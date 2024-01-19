#include "../pch.h"
#include "Hud.h"

Hud* Hud::get_instance()
{
	return RVA_CAST(Hud*, Addresses::Hud::HudInstance);
}

bool Hud::is_window_focused()
{
	return get_window_focus() == Enums::WindowFocus::Focused;
}

Cursor* Hud::get_cursor()
{
	return RVA_CAST_THIS(Cursor*, Structures::Hud::Cursor);
}

Enums::WindowFocus Hud::get_window_focus()
{
	return RVA_CAST_THIS(Enums::WindowFocus, Structures::Hud::WindowFocus);
}
