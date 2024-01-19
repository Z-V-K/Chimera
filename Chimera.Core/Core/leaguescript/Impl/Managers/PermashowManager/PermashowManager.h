#pragma once
#include "../Impl/UI/Permashow/Permashow.h"

class PermashowManager
{
	std::vector<Permashow*> permashows{ };
public:
	void on_draw();

	virtual Permashow* add_permashow(Menu* menu, const Vec2& position = { });
	virtual Permashow* get_permashow(const std::string& name);

	virtual bool remove_permashow(Permashow* permashow);
	void remove_permashows();
};

extern PermashowManager* g_permashow_manager;