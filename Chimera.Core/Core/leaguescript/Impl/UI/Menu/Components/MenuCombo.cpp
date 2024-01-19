#include "../Impl/UI/Menu/Components/MenuCombo.h"

#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuCombo::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_combo_handler(this);

	return handler;
}

void MenuCombo::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuCombo::on_update()
{
	MenuItem::on_update();
}

void MenuCombo::restore_default()
{
	*int_value = default_value;
}

ComponentType MenuCombo::get_type()
{
	return ComponentType::combo;
}

void MenuCombo::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
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

bool MenuCombo::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
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

bool MenuCombo::needs_type_change(rapidjson::Value& jsonRoot)
{
	return !jsonRoot.IsInt();
}
