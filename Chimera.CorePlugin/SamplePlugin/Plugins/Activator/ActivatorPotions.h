#pragma once

namespace Activator
{
	class Potions : public Singleton<Potions>
	{
		MenuItem* enable{};
		MenuItem* potion_health{};

		MenuItem* cookie_health{};
		MenuItem* cookie_mana{};

		MenuItem* corrupting_pot_health{};
		MenuItem* corrupting_pot_mana{};
	public:
		void initialize();
		void on_unload();

		static void on_tick();
	};
}