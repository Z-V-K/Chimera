#include "../Impl/UI/Menu/MenuItem.h"

#include "../Imgui/imgui.h"

const std::string& MenuItem::get_key() const
{
	return name;
}

const std::string& MenuItem::get_name() const
{
	return display_name;
}

bool MenuItem::get_bool() const
{
	return bool_value ? *bool_value : false;
}

uint32_t MenuItem::get_color() const
{
	return ImColor(color_value[0], color_value[1], color_value[2], color_value[3]);
}

int MenuItem::get_int() const
{
	return int_value ? *int_value : 0;
}

bool MenuItem::is_visible()
{
	if (b_visibility)
		return *b_visibility;

	if (e_visibility)
		return e_visibility->get_bool();

	return true;
}

void MenuItem::set_bool(bool b)
{
	*bool_value = b;
}

void MenuItem::set_color(uint32_t col)
{
	const ImColor _col(col);

	color_value[0] = _col.Value.x;
	color_value[1] = _col.Value.y;
	color_value[2] = _col.Value.z;
	color_value[3] = _col.Value.w;
}

void MenuItem::set_int(int i)
{
	*int_value = i;
}

void MenuItem::set_on_update(const std::function<void()>& on_update)
{
	f_on_update = on_update;
}

void MenuItem::set_on_value_change(const std::function<void(MenuItem*)>& on_value_change)
{
	f_on_value_change = on_value_change;	
}

void MenuItem::set_tooltip(const std::string& tooltip)
{
	this->tooltip = tooltip;
}

void MenuItem::set_texture(void* texture)
{
	this->texture = texture;
	this->has_texture = true;
}

void MenuItem::set_texture_lua(LuaTexture texture)
{
	set_texture(texture.texture);	
}

void MenuItem::set_visibility(MenuItem* entry)
{
	e_visibility = entry;
}

void MenuItem::set_visibility(bool* vis)
{
	b_visibility = vis;
}

void MenuItem::on_update()
{
	if (f_on_update)
		f_on_update();

	if (b_visibility && !*b_visibility)
		visible = false;

	if (e_visibility && !e_visibility->get_bool())
		visible = false;
}