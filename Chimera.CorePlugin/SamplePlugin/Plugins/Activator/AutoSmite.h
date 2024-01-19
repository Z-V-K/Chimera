#pragma once

namespace Activator
{
	class AutoSmite : public Singleton<AutoSmite>
	{
		Spell* smite_spell{};

		MenuItem* enable{};

		MenuTab* monster_settings{};
		MenuItem* enable_buffs{};
		MenuItem* enable_baron{};
		MenuItem* enable_herald{};
		MenuItem* enable_drake{};
		MenuItem* enable_crab{};
		MenuItem* enable_big_monster_camps{};
		
	public:
		void initialize(SpellSlot* smite_slot);
		void on_unload();

		static void on_update();
		static void on_draw();
	};
}