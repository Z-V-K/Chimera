#include "../Impl/UI/Menu/Components/MenuColorPick.h"

#include "../Impl/UI/Menu/MenuSettings.h"

IDrawable* MenuColorPick::get_handler()
{
	if (handler == nullptr)
		handler = MenuSettings::get().theme->build_color_handler(this);

	return handler;
}

void MenuColorPick::on_draw(const Vec2& position)
{
	this->position = position;
	get_handler()->draw();
}

void MenuColorPick::on_update()
{
	MenuItem::on_update();
}

void MenuColorPick::restore_default()
{
	color_value[0] = default_value[0];
	color_value[1] = default_value[1];
	color_value[2] = default_value[2];
	color_value[3] = default_value[3];
}

ComponentType MenuColorPick::get_type()
{
	return ComponentType::colorpick;
}

void MenuColorPick::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (jsonRoot.IsNull())
	{
		jsonRoot.SetUint(get_color());
		cfg_data.colorValue = get_color();
	}

	else
	{
		cfg_data.colorValue = jsonRoot.GetUint();

		ImColor imcol{ cfg_data.colorValue };
		ImVec4 colV4{ imcol };

		color_value[0] = colV4.x;
		color_value[1] = colV4.y;
		color_value[2] = colV4.z;
		color_value[3] = colV4.w;
	}
}

bool MenuColorPick::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	if (get_color() != cfg_data.colorValue)
	{
		jsonRoot.SetUint(get_color());
		cfg_data.colorValue = get_color();

		if (f_on_value_change)
			f_on_value_change(this);
		
		return true;
	}

	return false;
}

bool MenuColorPick::needs_type_change(rapidjson::Value& jsonRoot)
{
	return !jsonRoot.IsUint();
}
