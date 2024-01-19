#pragma once

struct ImColor;

class Utils final
{
public:
	static std::string to_lower_case(const std::string_view& str);
	static bool is_valid_string(const char* str);
	static void message_box_ptr(uintptr_t ptr);
	static uint32_t imcolor_to_hex(ImColor col);
};
