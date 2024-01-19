#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"

class Chat final
{
private:
	__forceinline void* menu_gui();

public:
	const Vec2& get_position();
	int get_times_open();
	static Chat* instance();
	bool is_open();
	virtual void print_chat(const std::string& message);
	virtual void send_chat(std::string& message, bool all_chat);
};