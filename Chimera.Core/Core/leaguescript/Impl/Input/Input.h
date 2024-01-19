#pragma once

#include "../Impl/Vector/Vector.h"

class Input final
{
public:
	virtual bool is_key_down(uint32_t key);
	virtual bool is_key_up(uint32_t key);
	virtual bool is_key_pressed(uint32_t key);
	virtual Vec2 get_cursor_screen_position();

	static bool core_is_key_down(uint32_t key);
	static bool core_is_key_up(uint32_t key);
	static bool core_is_key_pressed(uint32_t key);
	static Vec2 core_get_cursor_screen_position();
};

extern Input* g_input;