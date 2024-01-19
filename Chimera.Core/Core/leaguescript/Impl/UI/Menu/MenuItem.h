#pragma once
#include "../../../SDK/LUA/LuaTexture.h"
#include "../Impl/UI/Menu/AMenuComponent.h"
#include "../SDK/LUA/LuaIncludes.h"

struct EntryConfig
{
	bool boolValue = false;
	bool boolValue2 = false;
	int intValue = INT_MAX;
	uint32_t colorValue = 0x0;
};

class MenuItem :
    public AMenuComponent
{
protected:
	EntryConfig cfg_data{ };

	bool*	bool_value = nullptr;
	int*	int_value = nullptr;

	bool*	  b_visibility = nullptr;
	MenuItem* e_visibility = nullptr;

	std::function<void()> f_on_update = nullptr;
	std::function<void(MenuItem*)> f_on_value_change = nullptr;
public:

	bool is_main_title = false;

	float color_value[4] { 0.f, 0.f, 0.f, 0.f };
	std::string tooltip;

	MenuItem(const std::string& name, const std::string& displayName, const std::string& icon) :
		AMenuComponent(name, displayName, icon)
	{ }

	~MenuItem()
	{
		delete	 bool_value;
		delete	 int_value;
		delete	 b_visibility;
		delete   e_visibility;
	}

	bool is_visible();

	virtual const std::string& get_key() const;
	virtual const std::string& get_name() const;

	virtual bool			get_bool() const;
	virtual int				get_int() const;
	virtual uint32_t		get_color() const;

	virtual void			set_bool(bool b);
	virtual void			set_int(int i);
	virtual void			set_color(uint32_t col);

	virtual void			set_visibility(bool* vis);
	virtual void			set_visibility(MenuItem* entry);

	virtual void			set_on_update(const std::function<void()>& on_update);
	virtual void			set_on_value_change(const std::function<void(MenuItem*)>& on_value_change);
	virtual void			set_tooltip(const std::string& tooltip);
	virtual void			set_texture(void* texture);

	void set_texture_lua(LuaTexture texture);

	virtual void			on_update() override;
};

