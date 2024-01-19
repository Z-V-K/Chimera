#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuButton.h"

class ButtonBaseTheme : public ADrawable<MenuButton>
{
public:
    ButtonBaseTheme(MenuButton* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

