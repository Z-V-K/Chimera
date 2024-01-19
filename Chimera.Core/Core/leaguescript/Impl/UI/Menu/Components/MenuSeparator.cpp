#include "../Impl/UI/Menu/Components/MenuSeparator.h"

#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuSeparator::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_separator_handler(this);

	return handler;
}

void MenuSeparator::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuSeparator::on_update()
{
	MenuItem::on_update();
}

void MenuSeparator::restore_default()
{
	
}

ComponentType MenuSeparator::get_type()
{
	return ComponentType::separator;
}

void MenuSeparator::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	
}

bool MenuSeparator::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	return false;
}

bool MenuSeparator::needs_type_change(rapidjson::Value& jsonRoot)
{
	return !jsonRoot.IsNull();
}
