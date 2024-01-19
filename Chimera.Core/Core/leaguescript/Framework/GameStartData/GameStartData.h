#pragma once

#include "../Framework/Enums/GameStartDataEnums.h"

class GameStartData
{
public:
	GameStartData* instance();

	const char* get_mission_mode();
	Enums::MapID get_map_id();
	uint64_t get_region();
	uint64_t get_game_id();
	const char* get_game_type();
	const char* get_player_ip();
	const char* get_game_name();
};