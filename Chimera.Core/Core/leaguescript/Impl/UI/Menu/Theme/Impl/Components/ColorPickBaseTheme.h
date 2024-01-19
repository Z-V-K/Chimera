#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuColorPick.h"

class ColorPickBaseTheme : public ADrawable<MenuColorPick>
{
private:
    bool popupToggled = false;
public:
    ColorPickBaseTheme(MenuColorPick* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

