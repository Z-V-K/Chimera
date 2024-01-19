#pragma once

namespace Enums
{
	enum class OrbwalkerMode : uint32_t
	{
		None = 0,
		Combo = 1 << 0,
		LaneClear = 1 << 1,
		Harass = 1 << 2,
		LastHit = 1 << 3,
		Flee = 1 << 4
	};
}


class OrbwalkerManager
{
private:
	typedef Enums::OrbwalkerMode(*fn_get_mode)();
    fn_get_mode _get_mode = nullptr;
public:
    virtual void setCallbacks(
		fn_get_mode get_mode
    );

    virtual Enums::OrbwalkerMode get_mode();

    void remove_callbacks();
};

extern OrbwalkerManager* g_orbwalker_manager;