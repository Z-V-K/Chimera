#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Theme/ITheme.h"
#include "../Impl/UI/Menu/Components/MenuBool.h"
#include "../Impl/UI/Menu/Components/MenuButton.h"
#include "../Impl/UI/Menu/Components/MenuColorPick.h"
#include "../Impl/UI/Menu/Components/MenuKeyBind.h"
#include "../Impl/UI/Menu/Components/MenuCombo.h"
#include "../Impl/UI/Menu/Components/MenuSeparator.h"
#include "../Impl/UI/Menu/Components/MenuSlider.h"

class BaseTheme :
    public ITheme
{
public:
    ADrawable<MenuBool>* build_bool_handler(MenuBool* component) override;
    ADrawable<MenuButton>* build_button_handler(MenuButton* component) override;
    ADrawable<MenuColorPick>* build_color_handler(MenuColorPick* component) override;
    ADrawable<MenuKeyBind>* build_key_bind_handler(MenuKeyBind* component) override;
    ADrawable<MenuCombo>* build_combo_handler(MenuCombo* component) override;
    ADrawable<Menu>* build_menu_handler(Menu* component) override;
    ADrawable<MenuSeparator>* build_separator_handler(MenuSeparator* component) override;
    ADrawable<MenuSlider>* build_slider_handler(MenuSlider* component) override;

    void draw() override;
};

