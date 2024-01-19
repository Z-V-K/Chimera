#pragma once

#include <rapidjson/document.h>

#include "Translator.h"
#include "../Impl/Vector/Vector.h"

class Menu;
class IDrawable;

enum ComponentType
{
	checkbox,
    slider,
    menu,
    colorpick,
    keybind,
    separator,
    button,
    combo
};

class AMenuComponent
{
public:
    float menu_width_cached = 0.f;
    bool reset_width = true;

    bool dont_save = false;
    std::string name;
    std::string display_name;
    std::string permashow_text;
    Menu* parent = nullptr;
    bool root = false;
    bool toggled = false;
    bool visible = true;
    Vec2 position{ };

    std::string icon;
    bool has_texture = false;
    void* texture = nullptr;

    IDrawable* handler = nullptr;

    AMenuComponent(const std::string& name, const std::string& display_name, const std::string& icon = "")
    {
        if (name.empty() || display_name.empty())
            throw std::invalid_argument("Please enter a valid name and display name");

        this->display_name = Translator::translate(display_name);
        this->name = name;
        this->icon = icon;
    }

    float get_menu_width(bool force = false);
    void set_menu_width(float width);

    const std::string& get_key();
    const std::string& get_name();

    void toggle();

    virtual IDrawable* get_handler() = 0;
    virtual void on_draw(const Vec2& position) = 0;
    virtual void on_update() = 0;
    virtual void restore_default() = 0;
    virtual void init_from_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) = 0;
    virtual bool update_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) = 0;
    virtual bool needs_type_change(rapidjson::Value& json_root) = 0;
	virtual void set_reset_width();

    virtual ComponentType get_type() = 0;
};
