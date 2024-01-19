#pragma once
struct lua_State;

class LuaExporter
{
public:
    static void export_texture(lua_State* state);
    static void export_globals(lua_State* state);
    static void export_entitylist(lua_State* state);
    static void export_gameobject(lua_State* state);
    static void export_missileclient(lua_State* state);
    static void export_path_controller_common(lua_State* state);
    static void export_obj_manager(lua_State* state);
    static void export_spellslot(lua_State* state);
    static void export_spelldata(lua_State* state);
    static void export_itemslot(lua_State* state);
    static void export_spellcastinfo(lua_State* state);
    static void export_buff(lua_State* state);
    static void export_navmesh(lua_State* state);
    static void export_callbacks_manager(lua_State* state);
    static void export_scheduler(lua_State* state);
    static void export_draw_manager(lua_State* state);
    static void export_game(lua_State* state);
    static void export_minimap(lua_State* state);
    static void export_cursor(lua_State* state);
    static void export_input(lua_State* state);
    static void export_renderer(lua_State* state);
    static void export_menu_item(lua_State* state);
    static void export_menu(lua_State* state);
    static void export_menu_manager(lua_State* state);
    static void export_chat(lua_State* state);
    static void export_damage_lib(lua_State* state);
    static void export_orbwalker(lua_State* state);
    static void export_evade(lua_State* state);
    static void export_target_selector(lua_State* state);
    static void export_health_pred(lua_State* state);
    static void export_glow_manager(lua_State* state);
    static void export_permashow(lua_State* state);
    static void export_vector(lua_State* state);
    static void export_enums(lua_State* state);
};
