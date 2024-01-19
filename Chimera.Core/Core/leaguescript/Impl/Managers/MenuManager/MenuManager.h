#pragma once

#include <rapidjson/document.h>

#include "../Impl/UI/Menu/Components/Menu.h"
#include "../Impl/UI/Menu/MenuItem.h"


class MenuManager
{
	inline static std::vector<Menu*> menus{ };

public:

	inline static Menu* main_menu = nullptr;
	inline static MenuItem* show_menu = nullptr;
	inline static MenuItem* hide_drawings = nullptr;
	inline static MenuItem* show_console = nullptr;
	inline static MenuItem* show_console_menu_closed = nullptr;
	inline static MenuItem* zoom_hack = nullptr;
	inline static MenuItem* zoom_fov = nullptr;

	//inline static boost::property_tree::ptree config{ };

	static void init_menu();
	
	static Menu* create_menu(const std::string& key, const std::string& name, const std::string& icon = "");
	static bool delete_menu(Menu* menu);
	static bool delete_menu(const std::string& key);

	static void delete_menus();

	static void on_update();

	static void reset_width();

	static Menu* get_menu(const std::string& key);
	static const std::vector<Menu*>& get_menus();
	static std::vector<Menu*> get_visible_menus();

	static void draw();
};

 class ExportedMenuManager
 {
 public:
	 virtual Menu* create_menu(const std::string& key, const std::string& name, const std::string& icon = "");
	 virtual bool delete_menu(Menu* menu);
	 virtual bool delete_menu(const std::string& key);

	 virtual Menu* get_menu(const std::string& key);
	 virtual std::vector<Menu*> get_menus();
 };

extern ExportedMenuManager* g_exported_menu_manager;