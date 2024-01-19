#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuSlider.h"

class SliderBaseTheme : public ADrawable<MenuSlider>
{
public:
    SliderBaseTheme(MenuSlider* component) : ADrawable(component) { }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

