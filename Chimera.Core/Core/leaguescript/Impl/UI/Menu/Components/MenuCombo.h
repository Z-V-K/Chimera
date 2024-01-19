#pragma once
#include "../Impl/UI/Menu/MenuItem.h"

class MenuCombo : public MenuItem
{
private:
    int default_value;
public:
    const std::vector<std::string> values{ };

    MenuCombo(const std::string& name, const std::string& displayName, int defaultValue, const std::vector<std::string>& values, const std::string& icon) :
		MenuItem(name, displayName, icon),
		default_value(defaultValue),
		values(values)
    {
        int_value = new int(defaultValue);
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

