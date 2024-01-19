#pragma once

namespace Awareness
{
	namespace Menu
	{
		inline MenuTab* main_menu{};
		inline MenuTab* tab_spell_tracker{};
		inline MenuTab* tab_champion_tracker{};
		inline MenuTab* tab_jungle_tracker{};
		inline MenuTab* tab_ward_tracker{};
		inline MenuTab* tab_stasis_tracker{};
		inline MenuTab* tab_item_tracker{};
		inline MenuTab* tab_waypoints{};
		inline MenuTab* tab_range_indicator{};
		inline MenuTab* tab_hud{};
		inline MenuTab* tab_notifications{};
	}

	void initialize();
};

