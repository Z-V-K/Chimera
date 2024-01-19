#include "BoolBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

void BoolBaseTheme::draw()
{
    if (!component->visible)
        return;

    const auto container = ThemeUtils::get().get_container_rectangle(component);
    const bool hovering = ThemeUtils::get().is_cursor_inside(container);

    if (hovering && Input::core_is_key_pressed(VK_RBUTTON))
        component->restore_default();

    if (hovering && Input::core_is_key_pressed(VK_LBUTTON))
        component->set_bool(!component->get_bool());

    float y = ThemeUtils::get().get_container_rectangle(component).get_centered_text(component->display_name, CenteredFlags_VerticalCenter).y;
    float yIcon = y + 2.f;
    g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_text_offset, y }, component->display_name, MenuSettings::get().text_color->get_color());


    if (!component->has_texture)
    {
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_CHECK;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }

    if (component->tooltip.empty() || !hovering)
        return;

    ThemeUtils::get().draw_tooltip(component);
}

void BoolBaseTheme::on_wnd_proc()
{
    
}

float BoolBaseTheme::width()
{
    return ThemeUtils::get().calc_item_width(component);
}
