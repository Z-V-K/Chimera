#include "KeyBindBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

const Vec2 popupSize{ 80, 100 };

void KeyBindBaseTheme::draw()
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
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_KEYBOARD;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }

    float xButton = component->position.x + ThemeUtils::get().get_container_rectangle(component).width - MenuSettings::get().button_width - 25.f;

    const Rect buttonBoundaries{ { xButton, container.start.y + 3.f }, { xButton + MenuSettings::get().button_width, container.end().y - 3.f } };
    const Rect buttonPopupBoundaries{ { component->position.x + component->get_menu_width() - MenuSettings::get().mark_width - MenuSettings::get().container_icon_offset - 10.f, container.start.y }, 25.f, container.height };

    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().accent_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);
    g_draw_manager->menu_text({ buttonPopupBoundaries.start.x + 10.f, yIcon }, ICON_FA_ANGLE_RIGHT, popup_toggled ? MenuSettings::get().text_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());

    const Rect popupBoundaries{ { container.end().x + MenuSettings::get().tabs_margin, container.start.y }, { container.end().x + popupSize.x + MenuSettings::get().tabs_margin, container.start.y + MenuSettings::get().container_height }};

    if (!component->tooltip.empty() && hovering && !popup_toggled)
        ThemeUtils::get().draw_tooltip(component);

    if (Input::core_is_key_pressed(VK_LBUTTON))
    {
        const bool insideButton = ThemeUtils::get().is_cursor_inside(buttonPopupBoundaries);
        const bool insidePopup = ThemeUtils::get().is_cursor_inside(popupBoundaries);
        if (!insideButton && !insidePopup)
            popup_toggled = false;
        else if (insideButton)
			popup_toggled = !popup_toggled;

        const bool insideKeyInput = ThemeUtils::get().is_cursor_inside(buttonBoundaries);
        key_input_toggled = insideKeyInput && !key_input_toggled;
    }

    if (key_input_toggled)
    {
        bool valueChanged = false;
        for (auto i = 0; i < 5; i++) {
            if (ImGui::GetIO().MouseDown[i]) {
                switch (i) {
                case 0:
                    component->set_int(VK_LBUTTON);
                    break;
                case 2:
                    component->set_int(VK_MBUTTON);
                    valueChanged = true;
                    break;
                case 3:
                    component->set_int(VK_XBUTTON1);
                    valueChanged = true;
                	break;
                case 4:
                    component->set_int(VK_XBUTTON2);
                    valueChanged = true;
                	break;
                default:
                    break;
                }
            }
        }

        for (auto i = VK_BACK; i <= VK_RMENU; i++) {

            if (ImGui::GetIO().KeysDown[i]) {
                component->set_int(i == VK_ESCAPE ? 0 : i);
                valueChanged = true;
                break;
            }
        }

        if (valueChanged)
            key_input_toggled = false;
    }

    const std::string buttonText = key_input_toggled ? "?" : ThemeUtils::get().get_keybind_text_from_int(component->get_int());
    g_draw_manager->menu_text(buttonBoundaries.get_centered_text(buttonText, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), buttonText, MenuSettings::get().text_color->get_color());

    if (!popup_toggled)
        return;

    component->toggle();

    g_draw_manager->screen_rectangle(popupBoundaries.start, popupBoundaries.end(), MenuSettings::get().tab_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(popupBoundaries.start, popupBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

    hold_bool->on_draw(popupBoundaries.start);

    component->hold = hold_bool->get_bool();
}

void KeyBindBaseTheme::on_wnd_proc()
{

}

float KeyBindBaseTheme::width()
{
    return ThemeUtils::get().calc_item_width(component) + 25.f + MenuSettings::get().button_width + 25.f;
}
