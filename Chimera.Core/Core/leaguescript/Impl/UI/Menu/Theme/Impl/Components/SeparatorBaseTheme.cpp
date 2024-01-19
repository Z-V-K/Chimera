#include "SeparatorBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"

void SeparatorBaseTheme::draw()
{
    if (!component->visible)
        return;

    const auto container = ThemeUtils::get().get_container_rectangle(component, true);


    Vec2 textPos = container.get_centered_text(component->display_name, CenteredFlags_VerticalCenter | CenteredFlags_HorizontalCenter, false, component->is_main_title);

    if (component->is_main_title)
    {
        textPos.x -= 10.f;
    }

	g_draw_manager->menu_text(textPos, component->display_name, MenuSettings::get().text_color->get_color(), false, component->is_main_title);

    float y = container.start.y + container.height / 2;

    if (!component->is_main_title)
    {
        g_draw_manager->screen_line({ component->position.x + 5.f, y }, { textPos.x - 5.f, y }, MenuSettings::get().separator_color->get_color());
        g_draw_manager->screen_line({ textPos.x + ThemeUtils::get().calc_text_size(component->display_name).x + 5.f, y }, { container.end().x - 5.f, y }, MenuSettings::get().separator_color->get_color());
    }
    else
    {
        const float text_width = 73.f;
        const float text_start = 38.f;

        g_draw_manager->screen_line({ component->position.x + 5.f, y }, { component->position.x + text_start, y }, MenuSettings::get().separator_color->get_color());
        g_draw_manager->screen_line({ component->position.x + text_start + text_width, y }, { container.end().x - 5.f, y }, MenuSettings::get().separator_color->get_color());
    }
}

void SeparatorBaseTheme::on_wnd_proc()
{

}

float SeparatorBaseTheme::width()
{
    return ThemeUtils::get().calc_text_size(component->display_name).x + 40.f;
}
