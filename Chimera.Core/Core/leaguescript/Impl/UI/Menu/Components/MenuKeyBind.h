#pragma once
#include "../Impl/UI/Menu/MenuItem.h"

class MenuKeyBind : public MenuItem
{
    uint32_t default_key;
    bool default_hold;
    bool default_value;
public:
    bool hold;

    MenuKeyBind(const std::string& name, const std::string& displayName, bool hold, uint32_t default_key, bool default_value, const std::string& icon) :
		MenuItem(name, displayName, icon),
		default_key(default_key),
		default_hold(hold),
		default_value(default_value),
		hold(hold)
    {
        int_value = new int(default_key);
        bool_value = new bool(default_value);
    }

    void on_draw(const Vec2& position) override;
    void on_update() override;
    void restore_default() override;
    IDrawable* get_handler() override;
    ComponentType get_type() override;
    void init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool needs_type_change(rapidjson::Value& jsonRoot) override;
};

