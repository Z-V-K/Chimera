#pragma once

namespace Activator
{
	namespace Menu
	{
		inline MenuTab* main_menu{};

		inline MenuTab* auto_smite{};
		inline MenuTab* summoner_spells{};
		inline MenuTab* defensive_items{};
		inline MenuTab* offensive_items{};
		inline MenuTab* potions{};
		inline MenuTab* misc{};
	}

	void initialize();
};