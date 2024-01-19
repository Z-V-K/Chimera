#include "../Impl/UI/Menu/Components/MenuKeyBind.h"

#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuKeyBind::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_key_bind_handler(this);

	return handler;
}

void MenuKeyBind::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuKeyBind::on_update()
{
	MenuItem::on_update();

	if (hold)
	{
		*bool_value = Input::core_is_key_down(*int_value);
	}
	else if (Input::core_is_key_pressed(*int_value))
	{
		*bool_value = !(*bool_value);
	}
}

void MenuKeyBind::restore_default()
{
	hold = default_hold;
	*bool_value = default_value;
	*int_value = default_key;
}

ComponentType MenuKeyBind::get_type()
{
	return ComponentType::keybind;
}

void MenuKeyBind::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (!jsonRoot.HasMember(xorstr_("key")))
	{
		jsonRoot.AddMember("key", *int_value, allocator);
		cfg_data.intValue = *int_value;
	}
	else
	{
		cfg_data.intValue = jsonRoot[xorstr_("key")].GetInt();
		*int_value = cfg_data.intValue;
	}

	if (!jsonRoot.HasMember(xorstr_("hold")))
	{
		jsonRoot.AddMember("hold", hold, allocator);
		cfg_data.boolValue2 = hold;
	}
	else
	{
		cfg_data.boolValue2 = jsonRoot[xorstr_("hold")].GetBool();
		hold = cfg_data.boolValue2;
	}

	if (!jsonRoot.HasMember(xorstr_("bool")))
	{
		jsonRoot.AddMember("bool", *bool_value, allocator);
		cfg_data.boolValue = *bool_value;
	}
	else
	{
		cfg_data.boolValue = jsonRoot[xorstr_("bool")].GetBool();
		*bool_value = cfg_data.boolValue;
	}
}

bool MenuKeyBind::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	bool changed = false;

	if (hold != cfg_data.boolValue2)
	{
		jsonRoot[xorstr_("hold")].SetBool(hold);
		cfg_data.boolValue2 = hold;

		changed = true;
	}
	
	if (*int_value != cfg_data.intValue)
	{
		jsonRoot[xorstr_("key")].SetInt(*int_value);
		cfg_data.intValue = *int_value;

		changed = true;
	}

	if (*bool_value != cfg_data.boolValue)
	{
		jsonRoot[xorstr_("bool")].SetBool(*bool_value);
		cfg_data.boolValue = *bool_value;

		changed = true;
	}

	if (changed)
	{
		if (f_on_value_change)
			f_on_value_change(this);
	}

	return changed;
}

bool MenuKeyBind::needs_type_change(rapidjson::Value& jsonRoot)
{
	return !jsonRoot.IsObject() || !jsonRoot[xorstr_("bool")].IsBool() || !jsonRoot[xorstr_("hold")].IsBool() || !jsonRoot[xorstr_("key")].IsInt();
}
