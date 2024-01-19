#pragma once
#include "../Impl/UI/Menu/Theme/Impl/Themes/BaseTheme.h"
#include "../Impl/Singleton/Singleton.h"

#include "../Imgui/imgui.h"

class MenuSettings : public singleton<MenuSettings>
{
public:
    Vec2 position { 50.f, 50.f };
    float container_width = 150.f;
    float container_height = 27.f;
    float container_text_offset = 30.f;
    float container_icon_offset = 5.f;
    float mark_width = 10.f;
    float tabs_margin = 2.f;
    float inner_margin = 3.f;
    float border_width = 1.2f;
    float button_width = 50.f;
    float slider_width = 100.f;

    int font_size = 16;

    MenuItem* tab_color           = nullptr;
    MenuItem* tab_border_color    = nullptr;
    MenuItem* slider_color        = nullptr;
    MenuItem* accent_color        = nullptr;
    MenuItem* hovered_tab_color   = nullptr;
    MenuItem* separator_color     = nullptr;
    MenuItem* text_color          = nullptr;

    MenuItem* icon_enabled_color  = nullptr;
    MenuItem* icon_disabled_color = nullptr;

    MenuItem* permashow_background_color = nullptr;

    ITheme* theme = new BaseTheme();
};
