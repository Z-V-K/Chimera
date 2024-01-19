#include "../pch.h"
#include "Minimap.h"

Minimap* g_minimap = new Minimap();

Minimap* Minimap::get_instance()
{
	static Minimap* instance = RVA_CAST(Minimap*, Addresses::Minimap::MinimapInstance);

	if (!instance)
		instance = RVA_CAST(Minimap*, Addresses::Minimap::MinimapInstance);

	return instance;
}

const Vec2& Minimap::get_position()
{
	static void* minimapHud = RVA_CAST_THIS(void*, Structures::Minimap::MinimapHud);

	return *reinterpret_cast<Vec2*>((uintptr_t) minimapHud + static_cast<uintptr_t>(Structures::Minimap::Position));
}

const Vec2& Minimap::get_size()
{
	static void* minimapHud = RVA_CAST_THIS(void*, Structures::Minimap::MinimapHud);

	return *reinterpret_cast<Vec2*>((uintptr_t)minimapHud + static_cast<uintptr_t>(Structures::Minimap::Size));
}

Vec2 Minimap::exported_get_position()
{
	if (const auto minimap = get_instance())
		return minimap->get_position();

	return { };
}

Vec2 Minimap::exported_get_size()
{
	if (const auto minimap = get_instance())
		return minimap->get_size();

	return { };
}