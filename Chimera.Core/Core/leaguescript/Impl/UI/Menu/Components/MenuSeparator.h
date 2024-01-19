#pragma once
#include "../Impl/UI/Menu/MenuItem.h"

class MenuSeparator : public MenuItem
{
public:
    MenuSeparator(const std::string& name, const std::string& displayName) :
		MenuItem(name, displayName, "")
    { }

    void on_draw(const Vec2& position) override;
    void on_update() override;
    void restore_default() override;
    IDrawable* get_handler() override;
    ComponentType get_type() override;

    void init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool needs_type_change(rapidjson::Value& jsonRoot) override;
};

