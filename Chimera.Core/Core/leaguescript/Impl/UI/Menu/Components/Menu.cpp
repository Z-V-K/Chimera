#include "../Impl/UI/Menu/Components/Menu.h"

#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

void Menu::on_draw(const Vec2& position)
{
    this->position = position;
    get_handler()->draw();
}

void Menu::on_update()
{
	if (bEnabled)
		enabled = *bEnabled;
	else if (eEnabled)
		enabled = eEnabled->get_bool();

	for (const auto& elt : components)
		elt->on_update();
}

void Menu::restore_default()
{

}

IDrawable* Menu::get_handler()
{
    if (handler == nullptr)
        handler = MenuSettings::get().theme->build_menu_handler(this);

    return handler;
}

void Menu::set_texture(void* menu_texture)
{
	if (menu_texture)
	{
		has_texture = true;
		texture = menu_texture;
	}
}

void Menu::set_texture_lua(LuaTexture menu_texture)
{
	set_texture(menu_texture.texture);
}

void Menu::set_enabled(bool* enabled)
{
	bEnabled = enabled;
}

void Menu::set_enabled(MenuItem* item)
{
	eEnabled = item;
}

void Menu::set_reset_width()
{
	for (const auto& elt : components)
		elt->set_reset_width();

	reset_width = true;
}

AMenuComponent* existsInComponents(const std::string& key, const std::list<AMenuComponent*>& components)
{
	for (const auto& elt : components)
	{
		if (elt->name == key)
			return elt;
	}

	return nullptr;
}

const std::string& Menu::get_key() const
{
	return name;
}

const std::string& Menu::get_name()const
{
	return display_name;
}

Menu* Menu::add_menu(const std::string& key, const std::string& name, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (Menu*) elt;

	Menu* menu = new Menu(key, name, icon, false);
	menu->parent = this;

	components.push_back(menu);

	MenuManager::reset_width();

	return menu;
}

MenuItem* Menu::add_button(const std::string& key, const std::string& name, const std::string& button_text, const std::function<void()>& func)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*) elt;

	MenuItem* item = new MenuButton(key, name, button_text, func);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_separator(const std::string& key, const std::string& name)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	MenuItem* item = new MenuSeparator(key, name);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_checkbox(const std::string& key, const std::string& name, bool value, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	MenuItem* item = new MenuBool(key, name, value, icon);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_color_pick(const std::string& key, const std::string& name, uint32_t default_value, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	const ImColor color{ default_value };
	float fColor[4]{ color.Value.x, color.Value.y, color.Value.z, color.Value.w };

	MenuItem* item = new MenuColorPick(key, name, fColor, icon);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_combo(const std::string& key, const std::string& name, int default_value, const std::vector<std::string>& values, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	MenuItem* item = new MenuCombo(key, name, default_value, values, icon);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_key(const std::string& key, const std::string& name, bool hold, int default_key, bool default_value, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	MenuItem* item = new MenuKeyBind(key, name, hold, default_key, default_value, icon);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

MenuItem* Menu::add_slider(const std::string& key, const std::string& name, int default_value, int min_value, int max_value, const std::string& icon)
{
	if (const auto elt = existsInComponents(key, components))
		return (MenuItem*)elt;

	MenuItem* item = new MenuSlider(key, name, default_value, min_value, max_value, icon);
	item->parent = this;

	components.push_back(item);

	MenuManager::reset_width();

	return item;
}

void Menu::init_from_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	for (const auto& entry : components)
	{
		if (entry->needs_type_change(jsonRoot[entry->get_key().c_str()]))
			jsonRoot.RemoveMember(entry->get_key().c_str());

		if (!jsonRoot.HasMember(entry->get_key().c_str()))
		{
			rapidjson::Value key(entry->get_key().c_str(), allocator);

			if (entry->get_type() == ComponentType::menu || entry->get_type() == ComponentType::keybind)
			{
				rapidjson::Value val(rapidjson::Value(rapidjson::kObjectType), allocator);
				jsonRoot.AddMember(key, val, allocator);
			}
			else
			{
				jsonRoot.AddMember(key, rapidjson::Value(), allocator);
			}
		}

		entry->init_from_config(jsonRoot[entry->get_key().c_str()], allocator);
	}
}

bool Menu::update_config(rapidjson::Value& jsonRoot, rapidjson::MemoryPoolAllocator<>& allocator)
{
	bool changed = false;

	for (const auto& entry : components)
	{
		if (entry->needs_type_change(jsonRoot[entry->get_key().c_str()]))
			jsonRoot.RemoveMember(entry->get_key().c_str());

		if (!jsonRoot.HasMember(entry->get_key().c_str()))
		{
			rapidjson::Value key(entry->get_key().c_str(), allocator);

			if (entry->get_type() == ComponentType::menu || entry->get_type() == ComponentType::keybind)
			{
				rapidjson::Value val(rapidjson::Value(rapidjson::kObjectType), allocator);
				jsonRoot.AddMember(key, val, allocator);
			}
			else
			{
				jsonRoot.AddMember(key, rapidjson::Value(), allocator);
			}
		}

		if (entry->update_config(jsonRoot[entry->get_key().c_str()], allocator))
			changed = true;
	}

	return changed;
}

bool Menu::needs_type_change(rapidjson::Value& jsonRoot)
{
	if (!jsonRoot.IsObject() || jsonRoot.IsNull())
		return true;

	if (jsonRoot.HasMember(skCrypt("bool")) || (jsonRoot.HasMember(skCrypt("hold")) && jsonRoot.HasMember(skCrypt("key")) && jsonRoot.HasMember(skCrypt("bool"))))
		return true;

	return false;
}

ComponentType Menu::get_type()
{
	return ComponentType::menu;
}

MenuItem* Menu::get_item(const std::string& key)
{
	for (const auto& elt : components)
	{
		if (elt->get_key() == key && elt->get_type() != ComponentType::menu)
			return (MenuItem*) elt;
	}

	return nullptr;
}

bool Menu::delete_item(MenuItem* item)
{
	for (const auto& e : components) {
		if (e == item) {
			components.remove(e);
			delete e;

			return true;
		}
	}

	return false;
}

bool Menu::delete_item(const std::string& key)
{
	MenuItem* entry = get_item(key);

	if (!entry)
		return false;

	components.remove(entry);
	delete entry;

	return true;
}
