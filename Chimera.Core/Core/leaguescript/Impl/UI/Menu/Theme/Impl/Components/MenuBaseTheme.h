#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/Menu.h"

class MenuBaseTheme : public ADrawable<Menu>
{
public:
    MenuBaseTheme(Menu* component) : ADrawable(component) { }

    bool hovering = false;

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

