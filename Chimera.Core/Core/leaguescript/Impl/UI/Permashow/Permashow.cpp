#include "Permashow.h"

#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/Input/Input.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

const Vec2 toggle_indicator_margin = { 8.f, 8.f };
const Vec2 text_margin = { 30.f, 0.f };
constexpr float element_height = 20.f;

Permashow::Permashow(Menu* menu, const Vec2& position)
{
	name = menu->get_name();
	const auto permashow_menu = menu->add_menu(menu->get_name() + "_permashow", "Permashow");
	pos_x = permashow_menu->add_slider(name + "_permashowX",
		"Position X",
		position.is_valid() ? (int)position.x : (int)(Minimap::get_instance()->get_position().x - Minimap::get_instance()->get_size().x - 200.f),
		0,
		(int)r3dRenderer::instance()->get_renderer_size().x);

	pos_y = permashow_menu->add_slider(name + "_permashowY",
		"Position Y",
		position.is_valid() ? (int)position.y : (int)Minimap::get_instance()->get_position().y,
		0,
		(int)r3dRenderer::instance()->get_renderer_size().y);
}

void Permashow::on_draw()
{
	if ((bDraw && !*bDraw) || (eDraw && !eDraw->get_bool()))
		return;

	reset_width = true; // until I find a better workaround for string items

	Rect bounding_box{ { (float)pos_x->get_int(), (float)pos_y->get_int() }, get_width() + 20.f, MenuSettings::get().container_height };
	const float total_height = element_height * elements.size();
	Rect total_bounding{ bounding_box.start - Vec2(2.f, 2.f), bounding_box.end() + Vec2(2.f, total_height + 2.f) };

	handle_drag(total_bounding);

	g_draw_manager->screen_rectangle(bounding_box.start - Vec2(2.f, 2.f), bounding_box.end() + Vec2(2.f, total_height + 2.f), MenuSettings::get().permashow_background_color->get_color(), 6, 1, true);
	g_draw_manager->screen_rectangle(bounding_box.start, bounding_box.end(), MenuSettings::get().permashow_background_color->get_color(), 0, 1, true);
	g_draw_manager->screen_line({ bounding_box.start.x + 8.f, bounding_box.end().y - 4.f }, bounding_box.end() - Vec2(8.f, 4.f), MenuSettings::get().separator_color->get_color(), 1);
	g_draw_manager->screen_text(bounding_box.get_centered_text(name, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), name, MenuSettings::get().text_color->get_color());

	bounding_box.start.y += MenuSettings::get().container_height;
	bounding_box.height = element_height;

	for (const auto& elt : elements)
	{
		const Vec2 pos = bounding_box.start;

		bool toggled = (elt->is_menu_item && elt->menu_item->get_bool()) || (elt->is_bool_item && *elt->bool_item);

		g_draw_manager->screen_rectangle(bounding_box.start, bounding_box.end(), MenuSettings::get().permashow_background_color->get_color(), 0, 1, true);
		g_draw_manager->menu_text({ pos.x + (elt->is_string_item ? 8.f : text_margin.x), bounding_box.get_centered_text(name, CenteredFlags_VerticalCenter, true).y }, elt->name, MenuSettings::get().text_color->get_color(), true);

		if (!elt->is_string_item)
			g_draw_manager->menu_text({ pos.x + toggle_indicator_margin.x, bounding_box.get_centered_text(name, CenteredFlags_VerticalCenter, true).y - 2.f }, ICON_FA_CIRCLE, toggled ? ImColor(0, 255, 0) : ImColor(255, 0, 0), true);

		if (elt->is_menu_item && elt->menu_item->get_type() == ComponentType::keybind)
		{
			const Rect button_box{ { bounding_box.end().x - MenuSettings::get().button_width + 10.f, bounding_box.start.y + 2.f }, bounding_box.end() - Vec2(0, 2.f)};
			const std::string key = ThemeUtils::get().get_keybind_text_from_int(elt->menu_item->get_int());
			//g_draw_manager->screen_rectangle(button_box.start, button_box.end(), MenuSettings::get().accent_color->get_color(), 0, 1, true);
			g_draw_manager->menu_text(button_box.get_centered_text(key, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), key, MenuSettings::get().accent_color->get_color(), true);
		}

		if (elt->is_string_item)
		{
			const Rect text_box{ { bounding_box.end().x - ThemeUtils::get().calc_text_size(*elt->string_item).x - 8.f, bounding_box.start.y }, bounding_box.end() };
			g_draw_manager->menu_text(text_box.get_centered_text(*elt->string_item, CenteredFlags_HorizontalCenter | CenteredFlags_VerticalCenter), *elt->string_item, MenuSettings::get().text_color->get_color(), true);
		}

		bounding_box.start.y += element_height;
	}
}

void Permashow::handle_drag(Rect bounding)
{
	Vec2 cursorScreenPos = Input::core_get_cursor_screen_position();

	if (Input::core_is_key_down(VK_LBUTTON) && ThemeUtils::get().is_cursor_inside(bounding))
	{
		if (!clicked)
			og_offset = cursorScreenPos - Vec2{ (float)pos_x->get_int(), (float)pos_y->get_int() };
		
		clicked = true;
	}
	else
	{
		clicked = false;
	}

	if (clicked)
	{
		pos_x->set_int(cursorScreenPos.x - og_offset.x);
		pos_y->set_int(cursorScreenPos.y - og_offset.y);
	}
}

float Permashow::get_width()
{
	if (reset_width)
	{
		width_cached = ThemeUtils::get().calc_text_size(name).x + 20.f;
		bool has_key_element = false;

		for (const auto& element : elements)
		{
			float width = ThemeUtils::get().calc_text_size(element->name).x + 50.f;
			if (!has_key_element && element->is_menu_item && element->menu_item->get_type() == ComponentType::keybind)
				has_key_element = true;

			if (element->is_string_item)
				width += ThemeUtils::get().calc_text_size(*element->string_item).x;
			

			if (width > width_cached)
				width_cached = width;
		}

		if (has_key_element)
			width_cached += 40.f;
		reset_width = false;
	}

	return width_cached;
}

bool Permashow::add_element(MenuItem* item, const std::string& custom_name)
{
	if (!item)
		return false;

	for (const auto& elt : elements)
	{
		if (elt->is_menu_item && elt->menu_item == item)
			return false;
	}

	elements.push_back(new PermashowElement{ custom_name.empty() ? item->get_name() : custom_name, item });
	reset_width = true;
	return true;
}

bool Permashow::add_element(const std::string& name, bool* item)
{
	if (!item)
		return false;

	for (const auto& elt : elements)
	{
		if (elt->is_bool_item && elt->name == name)
			return false;
	}

	elements.push_back(new PermashowElement{ name, item });
	reset_width = true;
	return true;
}

bool Permashow::add_element(const std::string& name, std::string* item)
{
	if (!item)
		return false;

	for (const auto& elt : elements)
	{
		if (elt->is_string_item && elt->name == name)
			return false;
	}

	elements.push_back(new PermashowElement{ name, item });
	reset_width = true;
	return true;
}

bool Permashow::remove_element_item(MenuItem* item)
{
	for (const auto& elt : elements)
	{
		if (elt->is_menu_item && elt->menu_item == item)
		{
			delete elt;
			elements.remove(elt);
			return true;
		}
	}

	return false;
}

bool Permashow::remove_element(const std::string& name)
{
	for (const auto& elt : elements)
	{
		if (elt->name == name)
		{
			delete elt;
			elements.remove(elt);
			return true;
		}
	}

	return false;
}

void Permashow::clear_elements() 
{
	for (const auto& elt : elements)
		delete elt;

	elements.clear();
}

void Permashow::set_draw(MenuItem* item)
{
	eDraw = item;
}

void Permashow::set_draw(bool* b)
{
	bDraw = b;
}

std::string Permashow::get_name() const
{
	return name;
}