#include "SliderBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

void SliderBaseTheme::draw()
{
    if (!component->visible)
        return;

    if (component->get_int() < component->min_value)
        component->set_int(component->min_value);
    if (component->get_int() > component->max_value)
        component->set_int(component->max_value);

    const auto container = ThemeUtils::get().get_container_rectangle(component);
    const bool hovering = ThemeUtils::get().is_cursor_inside(container);

    if (hovering && Input::core_is_key_pressed(VK_RBUTTON))
        component->restore_default();

    float y = container.get_centered_text(component->display_name, CenteredFlags_VerticalCenter).y;
    const float maxValueWidth = std::max(ThemeUtils::get().calc_text_size(std::to_string(component->min_value)).x, ThemeUtils::get().calc_text_size(std::to_string(component->max_value)).x);

    float yIcon = y + 1.f;
    g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_text_offset, y }, component->display_name, MenuSettings::get().text_color->get_color());

    if (!component->has_texture)
    {
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_EXCHANGE_ALT;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, MenuSettings::get().icon_enabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }

    float xButton = component->position.x + ThemeUtils::get().get_container_rectangle(component).width - MenuSettings::get().slider_width - maxValueWidth - 10.f;

    const Rect sliderBoundaries{ { xButton, container.start.y + MenuSettings::get().inner_margin + 5.f }, { xButton + MenuSettings::get().slider_width, container.end().y - MenuSettings::get().inner_margin - 5.f }};
    g_draw_manager->screen_rectangle(sliderBoundaries.start, sliderBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 1, MenuSettings::get().border_width);

    const Rect valueBoundaries{ { sliderBoundaries.end().x + 5.f, container.start.y }, { container.end().x - 5.f, container.end().y } };
    const std::string valueStr = std::to_string(component->get_int());
    g_draw_manager->menu_text(valueBoundaries.get_centered_text(valueStr, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), valueStr, MenuSettings::get().text_color->get_color());

    const float sliderPos = MenuSettings::get().slider_width * ((float)(component->get_int() - component->min_value) / (float)(abs(component->max_value - component->min_value)));
    g_draw_manager->screen_rectangle(sliderBoundaries.start, { sliderBoundaries.start.x + sliderPos, sliderBoundaries.end().y }, MenuSettings::get().slider_color->get_color(), 1, 1, true);

    const Rect grabBoundaries{ { sliderBoundaries.start.x, container.start.y }, { sliderBoundaries.end().x, container.end().y } };

    if (Input::core_is_key_down(VK_LBUTTON) && ThemeUtils::get().is_cursor_inside(grabBoundaries))
    {
        int newVal = std::round(component->min_value + ((double) ImGui::GetMousePos().x - (double) sliderBoundaries.start.x) * (double)(component->max_value - component->min_value) / (double) MenuSettings::get().slider_width);

        if (newVal < component->min_value)
            newVal = component->min_value;
        if (newVal > component->max_value)
            newVal = component->max_value;

    	component->set_int(newVal);
    }

    if (component->tooltip.empty() || !hovering)
        return;

    ThemeUtils::get().draw_tooltip(component);
}

void SliderBaseTheme::on_wnd_proc()
{

}

float SliderBaseTheme::width()
{
    const float maxValueWidth = std::max(ThemeUtils::get().calc_text_size(std::to_string(component->min_value)).x, ThemeUtils::get().calc_text_size(std::to_string(component->max_value)).x);

	return ThemeUtils::get().calc_item_width(component) + MenuSettings::get().slider_width + maxValueWidth + 10.f;
}
