#pragma once
#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/MenuBool.h"
#include "../Impl/UI/Menu/Components/MenuKeyBind.h"

class KeyBindBaseTheme : public ADrawable<MenuKeyBind>
{
    bool popup_toggled = false;
    bool key_input_toggled = false;
    MenuBool* hold_bool;
public:
    KeyBindBaseTheme(MenuKeyBind* component) : ADrawable(component)
    {
        hold_bool = new MenuBool(component->name + "_bool", "Hold", component->hold, "");
    }

    void draw() override;
    void on_wnd_proc() override;
    float width() override;
};

