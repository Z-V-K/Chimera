#pragma once

class EventSystem final {
public:
	static char* convert_event_to_name(int event_id);
	static bool apply_hooks();
};