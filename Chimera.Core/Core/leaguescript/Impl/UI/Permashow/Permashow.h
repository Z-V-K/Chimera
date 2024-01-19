#pragma once
#include "../Impl/UI/Menu/Components/Menu.h"
#include "../Impl/UI/Menu/MenuItem.h"
#include "../Framework/Hud/Minimap/Minimap.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Impl/UI/Menu/Theme/ThemeUtils.h"

struct PermashowElement
{
	std::string name;

	bool is_menu_item = false;
	MenuItem* menu_item = nullptr;

	bool is_bool_item = false;
	bool* bool_item = nullptr;

	bool is_string_item = false;
	std::string* string_item = nullptr;

	PermashowElement(const std::string& name, MenuItem* item) : is_menu_item(true), menu_item(item) { this->name = name; }
	PermashowElement(const std::string& name, bool* item) : is_bool_item(true), bool_item(item) { this->name = name; }
	PermashowElement(const std::string& name, std::string* item) : is_string_item(true), string_item(item) { this->name = name; }
};

class Permashow
{
	std::string name;
	std::list<PermashowElement*> elements{ };

	MenuItem* pos_x = nullptr;
	MenuItem* pos_y = nullptr;

	float width_cached = 0;
	bool reset_width = true;

	bool clicked = false;
	Vec2 og_offset = { };

	MenuItem* eDraw = nullptr;
	bool* bDraw = nullptr;
public:
	Permashow(Menu* menu, const Vec2& position);

	~Permashow()
	{
		for (auto& elt : elements)
			delete elt;

		elements.clear();
	}

	void on_draw();
	void handle_drag(Rect bounding);

	float get_width();

	virtual bool add_element(MenuItem* item, const std::string& custom_name = "");
	virtual bool add_element(const std::string& name, bool* item);
	virtual bool add_element(const std::string& name, std::string* item);

	virtual bool remove_element_item(MenuItem* item);
	virtual bool remove_element(const std::string& name);
	virtual void clear_elements();

	virtual void set_draw(MenuItem* item);
	virtual void set_draw(bool* b);

	virtual std::string get_name() const;
};