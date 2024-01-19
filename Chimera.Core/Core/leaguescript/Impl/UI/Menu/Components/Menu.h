#pragma once

#include "../Impl/UI/Menu/AMenuComponent.h"
#include "../Impl/UI/Menu/MenuItem.h"

class Menu : public AMenuComponent
{
public:
    bool toggle_visible = false;
    bool enabled = true;

    bool* bEnabled = nullptr;
    MenuItem* eEnabled = nullptr;

    std::list<AMenuComponent*> components;

    Menu(const std::string& name, const std::string& display_name, const std::string& menu_icon, const bool root = false)
        : AMenuComponent(name, display_name, menu_icon)
    {
        AMenuComponent::root = root;
    }

    ~Menu()
    {
        for (const auto& t : components)
            delete t;

        components.clear();
    }

    void on_draw(const Vec2& position) override;
    void on_update() override;
    void restore_default() override;
    IDrawable* get_handler() override;
    void init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator) override;
    bool needs_type_change(rapidjson::Value& jsonRoot) override;
    ComponentType get_type() override;

    virtual const std::string& get_key() const;
    virtual const std::string& get_name() const;

    virtual Menu* add_menu(const std::string& key, const std::string& name, const std::string& icon = ICON_FA_BARS);
    virtual MenuItem* add_separator(const std::string& key, const std::string& name);
    virtual MenuItem* add_checkbox(const std::string& key, const std::string& name, bool value, const std::string& icon = ICON_FA_CHECK);
    virtual MenuItem* add_slider(const std::string& key, const std::string& name, int default_value, int min_value, int max_value, const std::string& icon = ICON_FA_ARROWS_ALT_H);
    virtual MenuItem* add_color_pick(const std::string& key, const std::string& name, uint32_t default_value, const std::string& icon = ICON_FA_PALETTE);
    virtual MenuItem* add_combo(const std::string& key, const std::string& name, int default_value, const std::vector<std::string>& values, const std::string& icon = ICON_FA_LIST);
    virtual MenuItem* add_key(const std::string& key, const std::string& name, bool hold, int default_key, bool default_value, const std::string& icon = ICON_FA_KEYBOARD);
    virtual MenuItem* add_button(const std::string& key, const std::string& name, const std::string& button_text, const std::function<void()>& func);

    virtual void set_texture(void* menu_texture);
    void set_texture_lua(LuaTexture menu_texture);
    virtual void set_enabled(bool* enabled);
    virtual void set_enabled(MenuItem* item);

    virtual MenuItem* get_item(const std::string& key);

    virtual bool delete_item(MenuItem* item);
    virtual bool delete_item(const std::string& key);

    virtual void set_reset_width() override;
};
