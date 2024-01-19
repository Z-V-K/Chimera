#pragma once

#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/Menu.h"
#include "../Impl/UI/Menu/Components/MenuBool.h"
#include "../Impl/UI/Menu/Components/MenuButton.h"
#include "../Impl/UI/Menu/Components/MenuColorPick.h"
#include "../Impl/UI/Menu/Components/MenuKeyBind.h"
#include "../Impl/UI/Menu/Components/MenuCombo.h"
#include "../Impl/UI/Menu/Components/MenuSeparator.h"
#include "../Impl/UI/Menu/Components/MenuSlider.h"

class ITheme {
public:
    virtual ADrawable<MenuBool>* build_bool_handler(MenuBool* component) = 0;
    virtual ADrawable<MenuButton>* build_button_handler(MenuButton* component) = 0;
    virtual ADrawable<MenuColorPick>* build_color_handler(MenuColorPick* component) = 0;
    virtual ADrawable<MenuKeyBind>* build_key_bind_handler(MenuKeyBind* component) = 0;
    virtual ADrawable<MenuCombo>* build_combo_handler(MenuCombo* component) = 0;
    virtual ADrawable<Menu>* build_menu_handler(Menu* component) = 0;
    virtual ADrawable<MenuSeparator>* build_separator_handler(MenuSeparator* component) = 0;
    virtual ADrawable<MenuSlider>* build_slider_handler(MenuSlider* component) = 0;

    virtual void draw() = 0;
};
