#include "ButtonBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

void ButtonBaseTheme::draw()
{
    if (!component->visible)
        return;

    const auto container = ThemeUtils::get().get_container_rectangle(component);
    const bool hovering = ThemeUtils::get().is_cursor_inside(container);

    float y = container.get_centered_text(component->display_name, CenteredFlags_VerticalCenter).y;
    float yIcon = y + 1.f;
    g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_text_offset, y }, component->display_name, MenuSettings::get().text_color->get_color());

    if (!component->has_texture)
    {
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_BARS;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, MenuSettings::get().icon_enabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }

    float xButton = component->position.x + ThemeUtils::get().get_container_rectangle(component).width - ThemeUtils::get().calc_text_size(component->button_text).x - 15.f;
    float buttonTextSize = ThemeUtils::get().calc_text_size(component->button_text).x;

    const Rect buttonBoundaries{ { xButton, container.start.y + MenuSettings::get().inner_margin }, { xButton + buttonTextSize + 10.f, container.end().y - MenuSettings::get().inner_margin }};

    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().accent_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);
    g_draw_manager->menu_text({ xButton + 5.f, y }, component->button_text, MenuSettings::get().text_color->get_color());

    if (ThemeUtils::get().is_cursor_inside(buttonBoundaries) && Input::core_is_key_pressed(VK_LBUTTON))
        component->func();

    if (component->tooltip.empty() || !hovering)
        return;

    ThemeUtils::get().draw_tooltip(component);
}

void ButtonBaseTheme::on_wnd_proc()
{

}

float ButtonBaseTheme::width()
{
    return ThemeUtils::get().calc_item_width(component) + ThemeUtils::get().calc_text_size(component->button_text).x + 15.f;
}
