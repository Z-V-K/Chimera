#include "../Awareness.h"
#include "../Colors.h"

#pragma once
namespace Awareness::ItemTracker
{
	namespace Menu
	{
		inline MenuItem* item_tracker_myself{};
		inline MenuItem* item_tracker_enemies{};
		inline MenuItem* item_tracker_allies{};
	}

	static void on_draw();
	void draw_items(GameObject* hero);

	void initialize();
	void on_unload();
};