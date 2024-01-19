#include "ColorPickBaseTheme.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

const Vec2 popupSize { 200.f, 170.f };

void ColorPickBaseTheme::draw()
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
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_PALETTE;
        g_draw_manager->menu_text({ component->position.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, MenuSettings::get().icon_enabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
        g_draw_manager->texture(component->texture, { component->position.x + MenuSettings::get().container_icon_offset, component->position.y + MenuSettings::get().inner_margin }, texSize, 0, component->get_bool() ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }
    float xButton = component->position.x + ThemeUtils::get().get_container_rectangle(component).width - MenuSettings::get().button_width - 5.f;

    const Rect buttonBoundaries{ { xButton, container.start.y + MenuSettings::get().inner_margin }, {xButton + MenuSettings::get().button_width, container.end().y - MenuSettings::get().inner_margin }};

    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), ImColor(0, 0, 0), 2, 1, true);
    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), component->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(buttonBoundaries.start, buttonBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

    const Rect popupBoundaries{ { container.end().x + MenuSettings::get().tabs_margin, container.start.y }, { container.end().x + popupSize.x + MenuSettings::get().tabs_margin, container.start.y + popupSize.y }};

    if (Input::core_is_key_pressed(VK_LBUTTON))
    {
        if (ThemeUtils::get().is_cursor_inside(buttonBoundaries))
            popupToggled = true;
        else if (popupToggled && !ThemeUtils::get().is_cursor_inside(popupBoundaries))
            popupToggled = false;
    }

    if (!component->tooltip.empty() && hovering && !popupToggled)
    	ThemeUtils::get().draw_tooltip(component);

    if (!popupToggled)
        return;

    component->toggle();

    g_draw_manager->screen_rectangle(popupBoundaries.start, popupBoundaries.end(), MenuSettings::get().tab_color->get_color(), 2, 1, true);
    g_draw_manager->screen_rectangle(popupBoundaries.start, popupBoundaries.end(), MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

    ImGui::SetNextWindowPos({ popupBoundaries.start.x, popupBoundaries.start.y });

    if (ImGui::Begin(xorstr_("##colorpickpopup"), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
    {
        // R,G,B buttons style
        ImGui::PushStyleColor(ImGuiCol_FrameBg, MenuSettings::get().accent_color->get_color());
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, MenuSettings::get().accent_color->get_color());
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, MenuSettings::get().accent_color->get_color());

        // R,G,B buttons font
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

        ImGui::ColorPicker4(xorstr_("##noname"), component->color_value, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar);

    	ImGui::PopFont();
    	ImGui::PopStyleColor(3);

    	ImGui::End();
    }
}

void ColorPickBaseTheme::on_wnd_proc()
{

}

float ColorPickBaseTheme::width()
{
    return ThemeUtils::get().calc_item_width(component) + MenuSettings::get().button_width + 10.f;
}
