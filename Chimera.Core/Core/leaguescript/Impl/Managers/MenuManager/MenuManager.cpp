#include "../pch.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "../Imgui/imgui.h"
#include "../Impl/Managers/DrawManager/DrawManager.h"
#include "../Impl/UI/Menu/MenuSettings.h"
#include "../Imgui/imgui_internal.h"
#include "../Framework/Hud/Zoom/Zoom.h"

ExportedMenuManager* g_exported_menu_manager = new ExportedMenuManager();

void MenuManager::init_menu()
{
	main_menu = MenuManager::create_menu(xorstr_("coremenu"), xorstr_("Core"), ICON_FA_COG);

	show_menu = main_menu->add_key(xorstr_("showmenu"), xorstr_("Menu key"), false, VK_INSERT, true);
	hide_drawings = main_menu->add_key(xorstr_("hidedrawings"), xorstr_("Hide drawings"), false, VK_F2, false);

	const auto consoleMenu = main_menu->add_menu(xorstr_("console"), xorstr_("Console"), ICON_FA_TERMINAL);
	show_console = consoleMenu->add_key(xorstr_("showconsole"), xorstr_("Show console"), false, 'L', true);
	show_console_menu_closed = consoleMenu->add_checkbox(xorstr_("showconsolemenuclosed"), xorstr_("^- even when menu closed"), true);

	consoleMenu->set_enabled(show_console);

	const auto zoomMenu = main_menu->add_menu(xorstr_("zoom"), xorstr_("Zoom"), ICON_FA_SEARCH);
	zoom_hack = zoomMenu->add_slider(xorstr_("zoomhack"), xorstr_("Max zoom"), 600, 600, 1500);
	zoom_hack->set_on_update([] {
		static float zoom_hack_val = 0.f;

		if (zoom_hack->get_int() != (int) zoom_hack_val)
		{
			Zoom::set_max_zoom((float) zoom_hack->get_int());
			zoom_hack_val = (float) zoom_hack->get_int();
		}
	});

	zoom_fov = zoomMenu->add_slider(xorstr_("zoomfov"), xorstr_("Camera FOV"), 40, 40, 60);
	zoom_fov->set_on_update([] {
	static float zoom_fov_val = 0.f;

	if (zoom_fov->get_int() != (int) zoom_fov_val)
	{
		Zoom::set_camera_angle((float) zoom_fov->get_int());
		zoom_fov_val = (float) zoom_fov->get_int();
	}
});

	const auto themeMenu = main_menu->add_menu(xorstr_("theme"), xorstr_("Theme"), ICON_FA_PAINT_BRUSH_ALT);
	MenuSettings::get().tab_color = themeMenu->add_color_pick(xorstr_("tabcolor"), xorstr_("Tab color"), ImColor{ 45, 50, 80, 230 });
	MenuSettings::get().tab_border_color = themeMenu->add_color_pick(xorstr_("tabbordercolor"), xorstr_("Tab border color"), ImColor{ 66, 71, 105 });
	MenuSettings::get().accent_color = themeMenu->add_color_pick(xorstr_("accentcolor"), xorstr_("Accent color"), ImColor{ 244, 175, 180 });
	MenuSettings::get().slider_color = themeMenu->add_color_pick(xorstr_("slidercolor"), xorstr_("Slider color"), ImColor{ 244, 175, 180 });
	MenuSettings::get().separator_color = themeMenu->add_color_pick(xorstr_("separatorcolor"), xorstr_("Separator color"), ImColor{ 103, 111, 157 });
	MenuSettings::get().text_color = themeMenu->add_color_pick(xorstr_("textcolor"), xorstr_("Text color"), ImColor{ 255, 255, 255 });
	MenuSettings::get().icon_enabled_color = themeMenu->add_color_pick(xorstr_("iconenabledcolor"), xorstr_("Icon enabled color"), ImColor{ 244, 175, 180 });
	MenuSettings::get().icon_disabled_color = themeMenu->add_color_pick(xorstr_("icondisabledcolor"), xorstr_("Icon disabled color"), ImColor{ 66, 71, 105 });
	MenuSettings::get().permashow_background_color = themeMenu->add_color_pick(xorstr_("permashowbgcolor"), xorstr_("Permashow background color"), ImColor{ 45, 25, 0, 130 });
}

Menu* MenuManager::create_menu(const std::string& key, const std::string& name, const std::string& icon)
{
	for (const auto& menu : menus)
	{
		if (menu->get_key() == key)
			return menu;
	}

	Menu* tab = new Menu(key, name, icon);

	menus.push_back(tab);

	return tab;
}

bool MenuManager::delete_menu(Menu* menu)
{
	const auto it = std::find(menus.begin(), menus.end(), menu);

	if (it == menus.end())
		return false;

	menus.erase(it);
	delete menu;

	return true;
}

bool MenuManager::delete_menu(const std::string& key)
{
	Menu* elt = get_menu(key);

	if (!elt)
		return false;

	const auto it = std::find(menus.begin(), menus.end(), elt);

	if (it == menus.end())
		return false;

	menus.erase(it);
	delete elt;

	return true;
}

void MenuManager::delete_menus()
{
	for (const auto& menu : menus)
		delete menu;

	menus.clear();
}

Menu* MenuManager::get_menu(const std::string& key)
{
	for (const auto& m : menus)
	{
		if (m->get_key() == key)
			return m;
	}

	return nullptr;
}

const std::vector<Menu*>& MenuManager::get_menus()
{
	return menus;
}

std::vector<Menu*> MenuManager::get_visible_menus()
{
	std::vector<Menu*> ret{ };

	for (const auto& menu : menus)
		if (menu->visible)
			ret.push_back(menu);

	return ret;
}

void MenuManager::on_update()
{
	for (const auto& menu : menus)
		menu->on_update();
}

void MenuManager::reset_width()
{
	for (const auto& elt : menus)
		elt->set_reset_width();
}

//namespace pt = boost::property_tree;

void MenuManager::draw()
{
	MenuSettings::get().theme->draw();
}

Menu* ExportedMenuManager::create_menu(const std::string& key, const std::string& name, const std::string& icon)
{
	return MenuManager::create_menu(key, name, icon);
}

bool ExportedMenuManager::delete_menu(Menu* menu)
{
	return MenuManager::delete_menu(menu);
}

bool ExportedMenuManager::delete_menu(const std::string& key)
{
	return MenuManager::delete_menu(key);
}

Menu* ExportedMenuManager::get_menu(const std::string& key)
{
	return MenuManager::get_menu(key);
}

std::vector<Menu*> ExportedMenuManager::get_menus()
{
	return MenuManager::get_menus();
}