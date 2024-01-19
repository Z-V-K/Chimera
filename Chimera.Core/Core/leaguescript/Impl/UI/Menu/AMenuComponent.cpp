#include "../Impl/UI/Menu/AMenuComponent.h"

#include "../Impl/UI/Menu/Theme/IDrawable.h"
#include "../Impl/UI/Menu/Components/Menu.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"

float AMenuComponent::get_menu_width(bool force)
{
    if (reset_width || force)
    {
        if (parent != nullptr)
        {
            float max = 0.f;
            for (const auto& elt : parent->components)
            {
                if (elt->visible && elt->get_handler()->width() > max)
                    max = elt->get_handler()->width();
            }

            menu_width_cached = max;
        }
        else
        {
            float max = 0.f;
            for (const auto& menu : MenuManager::get_menus())
            {
                if (menu->visible && menu->get_handler()->width() > max)
                    max = menu->get_handler()->width();
            }

            menu_width_cached = max;
        }

        reset_width = false;
    }

    return menu_width_cached;
}

void AMenuComponent::set_menu_width(float width)
{
    menu_width_cached = width;
}

const std::string& AMenuComponent::get_key()
{
    return name;
}

const std::string& AMenuComponent::get_name()
{
    return display_name;
}

void AMenuComponent::toggle()
{
    toggled = !toggled;

    if (!parent)
    {
	    for (const auto& elt : MenuManager::get_menus())
	    {
            if (elt->name == name)
                continue;

            elt->toggled = false;
	    }
    }
    else
    {
	    for (const auto& elt : parent->components)
	    {
            if (elt->name == name)
                continue;

            elt->toggled = false;
	    }
    }
}

void AMenuComponent::set_reset_width()
{
    reset_width = true;
}