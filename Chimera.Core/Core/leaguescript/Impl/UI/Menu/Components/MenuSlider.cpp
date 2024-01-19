#include "../Impl/UI/Menu/Components/MenuSlider.h"

#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuSlider::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_slider_handler(this);

	return handler;
}

void MenuSlider::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuSlider::on_update()
{
	MenuItem::on_update();
}

void MenuSlider::restore_default()
{
	*int_value = default_value;
}

ComponentType MenuSlider::get_type()
{
	return ComponentType::slider;
}

void MenuSlider::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (jsonRoot.IsNull())
	{
		jsonRoot.SetInt(*int_value);
		cfg_data.intValue = *int_value;
	}
	else
	{
		cfg_data.intValue = jsonRoot.GetInt();
		*int_value = cfg_data.intValue;
	}
}

bool MenuSlider::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (*int_value != cfg_data.intValue)
	{
		jsonRoot.SetInt(*int_value);
		cfg_data.intValue = *int_value;

		if (f_on_value_change)
			f_on_value_change(this);

		return true;
	}

	return false;
}

bool MenuSlider::needs_type_change(rapidjson::Value& jsonRoot)
{
	return !jsonRoot.IsInt();
}