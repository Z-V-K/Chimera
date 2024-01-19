#pragma once
#include "../Impl/UI/Menu/Components/MenuBool.h"

class BoolBaseTheme : public ADrawable<MenuBool>
{
public:
    BoolBaseTheme(MenuBool* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

