#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuSeparator.h"

class SeparatorBaseTheme : public ADrawable<MenuSeparator>
{
public:
    SeparatorBaseTheme(MenuSeparator* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

