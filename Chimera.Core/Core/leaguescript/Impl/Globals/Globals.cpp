#include "../pch.h"
#include "Globals.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

char* Globals::get_game_version()
{
	typedef char*(__fastcall* fnGetGameVersion)();
	static fnGetGameVersion fn = (fnGetGameVersion)MAKE_RVA(Addresses::Game::GameVersion);

	return x64RetSpoof::spoof_call(fn);
}

bool Globals::is_script_version_latest()
{
	std::string v1{ get_game_version() };
	std::string v2{ SCRIPT_VERSION };
	return v1 == v2;
}