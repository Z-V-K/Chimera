#include "../pch.h"
#include "GameTime.h"

GameClock* g_game_clock = new GameClock();

float GameClock::get_time() {
	return RVA_CAST(float, Addresses::Game::GameTime);
}

int GameClock::get_tick_count() {
	return static_cast<int>(get_time() * 1000);
}

float GameClock::exported_get_time()
{
	return get_time();
}

int GameClock::exported_get_tick_count()
{
	return get_tick_count();
}