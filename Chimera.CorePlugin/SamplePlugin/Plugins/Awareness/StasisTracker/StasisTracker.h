#include "../Awareness.h"
#include "../Colors.h"
#include "../../../SDK/Geometry.h"

#pragma once
namespace Awareness::StasisTracker
{
	namespace Menu
	{
		inline MenuItem* spell_tracker_myself{};
		inline MenuItem* spell_tracker_enemies{};
		inline MenuItem* spell_tracker_allies{};
	}

	static void on_draw();
	static void on_buff(Buff* buff, bool gain);

	void initialize();
	void on_unload();
};