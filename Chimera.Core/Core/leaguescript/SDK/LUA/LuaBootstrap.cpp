#include "LuaBootstrap.h"

#include "LuaIncludes.h"
#include "LuaExporter.h"

#include "../../Core/Context/Context.h"

inline std::map<lua_State*, luabridge::LuaRef> scripts { };

void report_errors(lua_State *state, int error_code) {
    if (error_code == 0) {
        return;
    }
    
    g_ctx->mConsole->log_error(xorstr_("[LUA] %s"), lua_tostring(state, -1));
    
    // remove error message from Lua state
    lua_pop(state, 1);
}

void load_library(lua_State* state, lua_CFunction library)
{
    lua_pushcfunction(state, library);
    lua_pushstring(state, "");
    lua_call(state, 1, 0);
    lua_pushcfunction(state, luaopen_package);
    lua_pushstring(state, LUA_LOADLIBNAME);
    lua_call(state, 1, 0);
}

void LuaBootstrap::load_scripts() {
    lua_State* state = luaL_newstate();

    load_library(state, luaopen_base);
    load_library(state, luaopen_math);
    load_library(state, luaopen_table);
    load_library(state, luaopen_string);

    LuaExporter::export_vector(state);
    LuaExporter::export_enums(state);
    LuaExporter::export_texture(state);
    LuaExporter::export_missileclient(state);
    LuaExporter::export_path_controller_common(state);
    LuaExporter::export_gameobject(state);
    LuaExporter::export_entitylist(state);
    LuaExporter::export_globals(state);
    LuaExporter::export_callbacks_manager(state);
    LuaExporter::export_obj_manager(state);
    LuaExporter::export_spellslot(state);
    LuaExporter::export_spelldata(state);
    LuaExporter::export_itemslot(state);
    LuaExporter::export_spellcastinfo(state);
    LuaExporter::export_buff(state);
    LuaExporter::export_navmesh(state);
    LuaExporter::export_scheduler(state);
    LuaExporter::export_draw_manager(state);
    LuaExporter::export_game(state);
    LuaExporter::export_minimap(state);
    LuaExporter::export_cursor(state);
    LuaExporter::export_input(state);
    LuaExporter::export_renderer(state);
    LuaExporter::export_menu_item(state);
    LuaExporter::export_menu(state);
    LuaExporter::export_menu_manager(state);
    LuaExporter::export_chat(state);
    LuaExporter::export_damage_lib(state);
    LuaExporter::export_orbwalker(state);
    LuaExporter::export_evade(state);
    LuaExporter::export_target_selector(state);
    LuaExporter::export_health_pred(state);
    LuaExporter::export_glow_manager(state);
    LuaExporter::export_permashow(state);
    LuaExporter::export_vector(state);

    luaL_dostring(state, xorstr_("ffi = require(\"ffi\")\n"
						 "ffi.cdef = nil\n"
						 "ffi.load = nil\n"
						 "ffi.C = nil\n"
						 "ffi.new = nil\n"
						 "ffi.typeof = nil\n"
						 "ffi.metatype = nil\n"
						 "ffi.gc = nil\n"
						 "ffi.sizeof = nil\n"
						 "ffi.alignof = nil\n"
						 "ffi.offsetof = nil\n"
						 "ffi.istype = nil\n"
						 "ffi.errno = nil\n"
						 "ffi.copy = nil\n"
						 "ffi.fill = nil\n"
						 "ffi.abi = nil\n"
						 "ffi.os = nil\n"
						 "ffi.arch = nil\n"
						 "ffi.cast = nil\n"));

    const int error_code = luaL_dofile(state, (g_ctx->plugins_path + xorstr_("test.lua")).c_str());
    report_errors(state, error_code);
    
    const auto on_load = luabridge::getGlobal(state, xorstr_("on_load"));
    const auto on_unload = luabridge::getGlobal(state, xorstr_("on_unload"));

    if (!on_load.isValid() || !on_load.isFunction() || !on_unload.isValid() || !on_unload.isFunction())
    	return;        

    const auto res = on_load();
    const bool loaded = res[0];
    if (!loaded)
        return;

    scripts.insert({ state, on_unload });
}

void LuaBootstrap::reload_scripts()
{
    for (const auto& script : scripts)
    {
        script.second();
    }

    scripts.clear();
    load_scripts();
}