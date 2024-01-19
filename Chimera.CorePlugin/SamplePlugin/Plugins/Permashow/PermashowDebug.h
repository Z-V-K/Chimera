#pragma once
namespace PermashowDebug
{
	inline Permashow* ps_process_spell;
	inline Permashow* ps_game_info;
	inline Permashow* ps_buff_manager;
	inline Permashow* ps_path_controller;
	inline Permashow* ps_missile_client;
	inline Permashow* ps_local_player_stats;
	inline Permashow* ps_local_player_info;
	inline Permashow* ps_item_list;
	inline Permashow* ps_particle_list;

	namespace Menu
	{
		inline MenuTab* main_menu{};
		inline MenuTab* draw_permashows{};

		inline MenuTab* process_spell{};
		inline MenuItem* process_spell_enable{};
		inline MenuTab* game_info{};
		inline MenuItem* game_info_enable{};
		inline MenuTab* buff_manager{};
		inline MenuItem* buff_manager_enable{};
		inline MenuTab* local_player_stats{};
		inline MenuItem* local_player_stats_enable{};
		inline MenuTab* local_player_info{};
		inline MenuItem* local_player_info_enable{};
		inline MenuTab* path_controller{};
		inline MenuItem* path_controller_enable{};
		inline MenuTab* item_list{};
		inline MenuItem* item_list_enable{};
		inline MenuTab* particle_list{};
		inline MenuItem* particle_list_enable{};
		inline MenuTab* missile_client{};
		inline MenuItem* missile_client_enable{};
	}

	static void on_process_spell(SpellCastInfo* processed_spell);
	static void on_game_tick();
	static void on_create_object(GameObject* obj);
	static void on_delete_object(GameObject* obj);

	void initialize();
	void init_permashows();
	void init_menu();
	std::string btos(bool x);
	std::string precision_to_string(float pVal);
};

