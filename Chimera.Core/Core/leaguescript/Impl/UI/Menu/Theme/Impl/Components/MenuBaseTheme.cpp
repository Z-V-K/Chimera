#include "MenuBaseTheme.h"

#include "../Impl/DirectX/DirectX.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

void MenuBaseTheme::draw()
{
    if (!component->visible)
        return;

    const Vec2 position1 = component->position;

    std::vector<AMenuComponent*> list{ };

    for (const auto& elt : component->components)
    {
        if (elt->visible)
            list.push_back(elt);
    }

    const auto container = ThemeUtils::get().get_container_rectangle(component);
    hovering = ThemeUtils::get().is_cursor_inside(container);

    if (hovering && Input::core_is_key_pressed(VK_LBUTTON))
        component->toggle();

    float y = container.get_centered_text(component->display_name, CenteredFlags_VerticalCenter).y;
    float yIcon = y + 1.f;

    if (!component->has_texture)
    {
        const std::string displayedIcon = component->icon > ICON_FA_CARAVAN_ALT && component->icon < ICON_FA_CARAVAN ? component->icon : ICON_FA_BARS;
        g_draw_manager->menu_text({ position1.x + MenuSettings::get().container_icon_offset, yIcon }, displayedIcon, component->enabled ? MenuSettings::get().icon_enabled_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());
    }
    else
    {
        const Vec2 texSize{ MenuSettings::get().container_height - MenuSettings::get().container_icon_offset, MenuSettings::get().container_height - MenuSettings::get().container_icon_offset };
    	g_draw_manager->texture(component->texture, { position1.x + MenuSettings::get().container_icon_offset, position1.y + MenuSettings::get().inner_margin }, texSize, 0, component->enabled ? ImColor(255, 255, 255) : ImColor(50, 50, 50));
    }

    g_draw_manager->menu_text({ position1.x + MenuSettings::get().container_text_offset, y }, component->display_name, MenuSettings::get().text_color->get_color());
    g_draw_manager->menu_text({ position1.x + component->get_menu_width() - MenuSettings::get().mark_width - MenuSettings::get().container_icon_offset, yIcon }, ICON_FA_ANGLE_RIGHT, component->toggled ? MenuSettings::get().accent_color->get_color() : MenuSettings::get().icon_disabled_color->get_color());

    if (component->toggled)
    {
        for (size_t i = 0; i < list.size(); i++)
        {
            if (AMenuComponent* aComponent = list[i])
            {
                Vec2 position2{ position1.x + component->get_menu_width() + MenuSettings::get().tabs_margin, position1.y + i * (MenuSettings::get().container_height + MenuSettings::get().tabs_margin) };

                g_draw_manager->screen_rectangle(position2, { position2.x + aComponent->get_menu_width(), position2.y + MenuSettings::get().container_height }, MenuSettings::get().tab_color->get_color(), 2, 1, true);
                g_draw_manager->screen_rectangle(position2, { position2.x + aComponent->get_menu_width(), position2.y + MenuSettings::get().container_height }, MenuSettings::get().tab_border_color->get_color(), 2, MenuSettings::get().border_width);

                aComponent->on_draw(position2);
            }
        }
    }
}

void MenuBaseTheme::on_wnd_proc()
{
    
}


float MenuBaseTheme::width()
{
    const auto w = ThemeUtils::get().calc_text_size(component->display_name).x + MenuSettings::get().container_text_offset * 2.f;
    return (w < 100 ? 50.f : 0.f) + w;
}

