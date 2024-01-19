#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuCombo.h"

class ListBaseTheme : public ADrawable<MenuCombo>
{
    bool popupToggled = false;
public:
    ListBaseTheme(MenuCombo* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

