#pragma once

namespace Activator
{
	class SummonerSpells : public Singleton<SummonerSpells>
	{
		MenuItem* enable{};

		MenuTab* cleanse_tab{};
		MenuItem* cleanse_enable{};
		MenuItem* cleanse_stun{};
		MenuItem* cleanse_taunt{};
		MenuItem* cleanse_berserk{};
		MenuItem* cleanse_polymorph{};
		MenuItem* cleanse_snare{};
		MenuItem* cleanse_fear{};
		MenuItem* cleanse_charm{};
		MenuItem* cleanse_blind{};
		MenuItem* cleanse_asleep{};
		MenuItem* cleanse_ignite{};
		MenuItem* cleanse_exhaust{};
		MenuItem* cleanse_delay{};
		MenuItem* cleanse_enemies{};
		MenuItem* cleanse_enemies_range{}; 

		MenuTab* heal_tab{};
		MenuItem* heal_enable{};
		MenuItem* heal_hp{};
		MenuItem* heal_incoming_dmg{};
		MenuItem* heal_not_level1{};
		MenuItem* heal_enemies{};
		MenuItem* heal_enemies_range{};

		MenuTab* barrier_tab{};
		MenuItem* barrier_enable{};
		MenuItem* barrier_hp{};
		MenuItem* barrier_incoming_dmg{};
		MenuItem* barrier_not_level1{};
        MenuItem* barrier_enemies{};
        MenuItem* barrier_enemies_range{};
		
		MenuTab* ignite_tab{};
		MenuItem* ignite_enable{};
		MenuItem* ignite_combo_only{};
		MenuItem* ignite_ignore_if_killable{};

	public:
		void initialize();
		void on_unload();

		bool should_cleanse(Buff* buff);

		static void on_update();
		static void on_draw();
		static void on_buff_gainlose(Buff* buff, bool gain);

	};
}