#pragma once
namespace Awareness::RangeIndicator
{
	namespace Menu
	{
		inline MenuTab* attack_range_group{};
		inline MenuItem* attack_range_indicator{};
		inline MenuItem* attack_range_indicator_color{};
		inline MenuItem* attack_range_thickness{};

		inline MenuTab* enemy_range_group{};
		inline MenuItem* enemy_range_indicator{};
		inline MenuItem* enemy_range_indicator_color{};
		inline MenuItem* enemy_range_thickness{};

		inline MenuTab* ally_range_group{};
		inline MenuItem* ally_range_indicator{};
		inline MenuItem* ally_range_indicator_color{};
		inline MenuItem* ally_range_thickness{};

		inline MenuTab* enemy_turret_range_group{};
		inline MenuItem* enemy_turret_range_indicator{};
		inline MenuItem* enemy_turret_range_indicator_color{};
		inline MenuItem* enemy_turret_range_thickness{};
	}

	static void on_draw();

	void initialize();
};