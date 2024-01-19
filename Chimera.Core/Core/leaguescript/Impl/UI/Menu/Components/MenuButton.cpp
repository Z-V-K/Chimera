#include "../Impl/UI/Menu/Components/MenuButton.h"

#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuButton::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_button_handler(this);

	return handler;
}

void MenuButton::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuButton::on_update()
{
	MenuItem::on_update();
}

void MenuButton::restore_default()
{
	
}

ComponentType MenuButton::get_type()
{
	return ComponentType::button;
}

void MenuButton::init_from_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator)
{
	
}

bool MenuButton::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	return false;
}

bool MenuButton::needs_type_change(rapidjson::Value& json_root)
{
	return !json_root.IsNull();
}
