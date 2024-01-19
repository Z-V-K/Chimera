#pragma once

struct lua_State;
class LuaBootstrap
{
public:
    static void load_scripts();
    static void reload_scripts();
};
