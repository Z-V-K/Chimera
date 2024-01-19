#include "../Impl/UI/Menu/Components/MenuBool.h"

#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

IDrawable* MenuBool::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_bool_handler(this);

	return handler;
}

void MenuBool::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuBool::on_update()
{
	MenuItem::on_update();
}

void MenuBool::restore_default()
{
	*bool_value = default_value;
}

ComponentType MenuBool::get_type()
{
	return ComponentType::checkbox;
}

void MenuBool::init_from_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (json_root.IsNull())
	{
		json_root.SetBool(*bool_value);
		cfg_data.boolValue = *bool_value;
	}
	else
	{
		cfg_data.boolValue = json_root.GetBool();
		*bool_value = cfg_data.boolValue;
	}
}

bool MenuBool::update_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (*bool_value != cfg_data.boolValue)
	{
		json_root.SetBool(*bool_value);
		cfg_data.boolValue = *bool_value;

		if (f_on_value_change)
			f_on_value_change(this);
		
		return true;
	}

	return false;
}

bool MenuBool::needs_type_change(rapidjson::Value& json_root)
{
	return !json_root.IsBool();
}