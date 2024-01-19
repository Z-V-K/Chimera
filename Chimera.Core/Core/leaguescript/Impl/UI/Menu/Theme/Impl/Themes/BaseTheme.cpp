#include "BaseTheme.h"

#include "../Impl/UI/Menu/Theme/Impl/Components/BoolBaseTheme.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/ButtonBaseTheme.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/ColorPickBaseTheme.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/KeyBindBaseTheme.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/ComboBaseTheme.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/MenuBaseTheme.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/SeparatorBaseTheme.h"
#include "../Impl/UI/Menu/Theme/Impl/Components/SliderBaseTheme.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"
#include "../Impl/Vector/Vector.h"
#include "../Imgui/imgui.h"

ADrawable<MenuBool>* BaseTheme::build_bool_handler(MenuBool* component)
{
    return new BoolBaseTheme(component);
}

ADrawable<MenuButton>* BaseTheme::build_button_handler(MenuButton* component)
{
    return new ButtonBaseTheme(component);
}

ADrawable<MenuColorPick>* BaseTheme::build_color_handler(MenuColorPick* component)
{
    return new ColorPickBaseTheme(component);
}

ADrawable<MenuKeyBind>* BaseTheme::build_key_bind_handler(MenuKeyBind* component)
{
    return new KeyBindBaseTheme(component);
}

ADrawable<MenuCombo>* BaseTheme::build_combo_handler(MenuCombo* component)
{
    return new ListBaseTheme(component);
}

ADrawable<Menu>* BaseTheme::build_menu_handler(Menu* component)
{
    return new MenuBaseTheme(component);
}

ADrawable<MenuSeparator>* BaseTheme::build_separator_handler(MenuSeparator* component)
{
    return new SeparatorBaseTheme(component);
}

ADrawable<MenuSlider>* BaseTheme::build_slider_handler(MenuSlider* component)
{
    return new SliderBaseTheme(component);
}

void BaseTheme::draw()
{
    Vec2 position1 = MenuSettings::get().position;

    const auto menus = MenuManager::get_visible_menus();

    if (menus.empty())
        return;

    const std::string title = xorstr_("키메라");

    const float menuWidth = menus[0]->get_menu_width();

    const Rect titleBoundaries{ position1, position1 + Vec2{ menuWidth, MenuSettings::get().container_height } };
    g_draw_manager->screen_rectangle(titleBoundaries.start, titleBoundaries.end(), MenuSettings::get().tab_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(titleBoundaries.start, titleBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

    MenuItem* titleBar = new MenuSeparator(xorstr_("title"), title);
    titleBar->is_main_title = true;
    titleBar->parent = nullptr;
    titleBar->on_draw(position1);
 
    position1 = position1 + Vec2{ 0.f, MenuSettings::get().container_height + MenuSettings::get().tabs_margin };

    for (size_t i = 0; i < menus.size(); i++)
    {
        Vec2 position2{ position1.x, position1.y + i * (MenuSettings::get().container_height + MenuSettings::get().tabs_margin) };

        g_draw_manager->screen_rectangle(position2, { position2.x + menuWidth, position2.y + MenuSettings::get().container_height }, MenuSettings::get().tab_color->get_color(), 2, 1, true);
        g_draw_manager->screen_rectangle(position2, { position2.x + menuWidth, position2.y + MenuSettings::get().container_height }, MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

        menus[i]->on_draw(position2);
    }

    delete titleBar;
}
