#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/MenuItem.h"

class MenuBool : public MenuItem
{
private:
    bool default_value;
public:
    MenuBool(const std::string& name, const std::string& display_name, bool defaultValue, const std::string& icon) :
        MenuItem(name, display_name, icon),
		default_value(defaultValue)
	{
        bool_value = new bool(defaultValue);
    }

    void on_draw(const Vec2& position) override;
    void on_update() override;
    void restore_default() override;
    IDrawable* get_handler() override;
    ComponentType get_type() override;
    void init_from_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool update_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool needs_type_change(rapidjson::Value& json_root) override;
};

