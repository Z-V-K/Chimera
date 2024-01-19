#pragma once
#include "../Impl/UI/Menu/MenuItem.h"

class MenuButton : public MenuItem
{
public:
	const std::function<void()> func;
	const std::string button_text;

	MenuButton(const std::string& name, const std::string& displayName, const std::string& buttonText, const std::function<void()>& func) :
		MenuItem(name, displayName, ""),
		func(func),
		button_text(buttonText)
	{ }

	void on_draw(const Vec2& position) override;
	void on_update() override;
	void restore_default() override;
	IDrawable* get_handler() override;
	ComponentType get_type() override;

	void init_from_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) override;
	bool update_config(rapidjson::Value& json_root, rapidjson::MemoryPoolAllocator<>& allocator) override;
	bool needs_type_change(rapidjson::Value& json_root) override;
};

