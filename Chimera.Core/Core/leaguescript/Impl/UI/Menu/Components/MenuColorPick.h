#pragma once
#include "../Impl/UI/Menu/MenuItem.h"
#include "../Imgui/imgui.h"

class MenuColorPick : public MenuItem
{
private:
    float default_value[4];
public:
    MenuColorPick(const std::string& name, const std::string& displayName, float defaultValue[4], const std::string& icon) :
        MenuItem(name, displayName, icon)
    {
        color_value[0] = defaultValue[0];
        color_value[1] = defaultValue[1];
        color_value[2] = defaultValue[2];
        color_value[3] = defaultValue[3];

        this->default_value[0] = defaultValue[0];
        this->default_value[1] = defaultValue[1];
        this->default_value[2] = defaultValue[2];
        this->default_value[3] = defaultValue[3];
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

