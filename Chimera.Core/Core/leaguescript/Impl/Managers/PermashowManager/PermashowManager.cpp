#include "PermashowManager.h"

PermashowManager* g_permashow_manager = new PermashowManager();

void PermashowManager::on_draw()
{
	for (const auto& permashow : permashows)
		permashow->on_draw();
}

Permashow* PermashowManager::add_permashow(Menu* menu, const Vec2& position)
{
	Permashow* permashow = new Permashow{ menu, position };
	permashows.push_back(permashow);

	return permashow;
}

Permashow* PermashowManager::get_permashow(const std::string& name)
{
	for (const auto& p : permashows)
	{
		if (p->get_name() == name)
			return p;
	}

	return nullptr;
}

bool PermashowManager::remove_permashow(Permashow* permashow)
{
	return false;
}

void PermashowManager::remove_permashows()
{
	for (const auto& elt : permashows)
		delete elt;

	permashows.clear();
}