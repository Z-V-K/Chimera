#pragma once
#include "../Impl/Vector/Vector.h"


class Minimap final
{
public:
	static Minimap* get_instance();

	const Vec2& get_position();
	const Vec2& get_size();

	virtual Vec2 exported_get_position();
	virtual Vec2 exported_get_size();
};

extern Minimap* g_minimap;