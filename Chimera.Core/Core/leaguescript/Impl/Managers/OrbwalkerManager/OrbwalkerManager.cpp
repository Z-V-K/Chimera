#include "../pch.h"
#include "OrbwalkerManager.h"

OrbwalkerManager* g_orbwalker_manager = new OrbwalkerManager();

void OrbwalkerManager::setCallbacks(
    fn_get_mode get_mode)
{
    _get_mode = get_mode;
}

Enums::OrbwalkerMode OrbwalkerManager::get_mode()
{
    if (_get_mode)
        return _get_mode();

    return Enums::OrbwalkerMode::None;
}

void OrbwalkerManager::remove_callbacks()
{
    _get_mode = nullptr;
}