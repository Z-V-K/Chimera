#include "ComboBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

float getLongestValueWidth(const std::vector<std::string>& values)
{
    float ret = 0.f;
    for (const auto& elt : values)
    {
        const float width = ThemeUtils::get().calc_text_size(elt).x + MenuSettings::get().container_icon_offset + 20.f;
        if (width > ret)
            ret = width;
    }

    return ret;
}

void ListBaseTheme::draw()
{
    if (!component->visible)
        return;

    const auto container = ThemeUtils::get().get_container_rectangle(component);
    const bool hovering = ThemeUtils::get().is_cursor_inside(container);

    if (hovering && Input::core_is_key_pressed(VK_RBUTTON))
        component->restore_default();

    float y = container.get_centered_text(component->display_name, CenteredFlags_VerticalCenter).y;
    float yIcon = y + 1.f;
    g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_text_offset, y }, component->display_name, MenuSettings::get().text_color->get_color());

    if (!component->has_texture)
    {
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_LIST;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, MenuSettings::get().icon_enabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }

    const float longestValueWidth = getLongestValueWidth(component->values);

	float xButton = component->position.x + ThemeUtils::get().get_container_rectangle(component).width - longestValueWidth - 25.f;

    const Rect buttonBoundaries{ { xButton, container.start.y + MenuSettings::get().inner_margin }, {xButton + longestValueWidth, container.end().y - MenuSettings::get().inner_margin }};
    const Rect buttonPopupBoundaries{ { component->position.x + component->get_menu_width() - MenuSettings::get().mark_width - MenuSettings::get().container_icon_offset - 10.f, container.start.y }, 25.f, container.height };

    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().accent_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);
    g_draw_manager->menu_text({ buttonPopupBoundaries.start.x + 10.f, yIcon }, ICON_FA_ANGLE_RIGHT, popupToggled ? MenuSettings::get().text_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    g_draw_manager->menu_text(buttonBoundaries.get_centered_text(component->values[component->get_int()], CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), component->values[component->get_int()], MenuSettings::get().text_color->get_color());

    const Rect popupBoundaries{ { container.end().x + MenuSettings::get().tabs_margin, container.start.y }, { container.end().x + longestValueWidth + MenuSettings::get().tabs_margin, container.start.y + component->values.size() * (MenuSettings::get().container_height + MenuSettings::get().tabs_margin) } };

    if (Input::core_is_key_pressed(VK_LBUTTON))
    {
        const bool insideButton = ThemeUtils::get().is_cursor_inside(buttonPopupBoundaries) || ThemeUtils::get().is_cursor_inside(buttonBoundaries);
        const bool insidePopup = ThemeUtils::get().is_cursor_inside(popupBoundaries);

        if (!insideButton && !insidePopup)
            popupToggled = false;
        if (insideButton)
            popupToggled = !popupToggled;
    }

    if (!component->tooltip.empty() && hovering && !popupToggled)
        ThemeUtils::get().draw_tooltip(component);

    if (!popupToggled)
        return;

    component->toggle();

    for (size_t i = 0; i < component->values.size(); i++)
    {
        const auto elt = component->values[i];

        const float y = popupBoundaries.start.y + i * (MenuSettings::get().container_height + MenuSettings::get().tabs_margin);
        const Rect boundaries{ { popupBoundaries.start.x, y }, { popupBoundaries.end().x, y + MenuSettings::get().container_height } };

        const float yText = boundaries.get_centered_text(elt, CenteredFlags_VerticalCenter).y;

        g_draw_manager->screen_rectangle(boundaries.start, boundaries.end(), MenuSettings::get().tab_color->get_color(), 2, 1, true);
        g_draw_manager->screen_rectangle(boundaries.start, boundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

        if (i == component->get_int())
			g_draw_manager->menu_text({ boundaries.start.x + MenuSettings::get().container_icon_offset, yText + 1.5f }, ICON_FA_CARET_RIGHT, MenuSettings::get().text_color->get_color());

    	g_draw_manager->menu_text({ boundaries.start.x + MenuSettings::get().container_icon_offset + 15.f, yText }, elt, MenuSettings::get().text_color->get_color());

        if (Input::core_is_key_pressed(VK_LBUTTON) && ThemeUtils::get().is_cursor_inside(boundaries))
            component->set_int(i);
    }
}

void ListBaseTheme::on_wnd_proc()
{

}

float ListBaseTheme::width()
{
    return ThemeUtils::get().calc_item_width(component) + getLongestValueWidth(component->values) + 25.f;
}
