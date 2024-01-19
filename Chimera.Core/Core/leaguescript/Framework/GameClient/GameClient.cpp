#include "GameClient.h"

GameClient* GameClient::instance()
{
	return RVA_CAST(GameClient*, Addresses::GameClient::GameClientInstance);
}

Enums::GameState GameClient::get_game_state()
{
	return RVA_CAST_THIS(Enums::GameState, Structures::GameClient::GameState);
}