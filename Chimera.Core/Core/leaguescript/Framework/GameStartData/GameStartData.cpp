#include "../pch.h"
#include "GameStartData.h"

#include "../Impl/Common/Common.h"
#include "../Impl/Common/Utils.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

GameStartData* GameStartData::instance()
{
	return RVA_CAST(GameStartData*, Addresses::GameStartData::GameStartDataInstance);
}

Enums::MapID GameStartData::get_map_id()
{
	typedef Enums::MapID(__fastcall* fnGetMapId)(GameStartData*);
	static fnGetMapId fn = (fnGetMapId)MAKE_RVA(Addresses::GameStartData::GetMapID);

	return x64RetSpoof::spoof_call(fn, this);
}

const char* GameStartData::get_mission_mode()
{
	typedef const char*(__fastcall* fnGetMissionMode)(GameStartData*);
	static fnGetMissionMode fn = (fnGetMissionMode)MAKE_RVA(Addresses::GameStartData::GetMissionMode);

	return x64RetSpoof::spoof_call(fn, this);
}

uint64_t GameStartData::get_game_id()
{
	typedef uint64_t (__fastcall* fnGetGameID)(GameStartData*);
	static fnGetGameID fn = (fnGetGameID)MAKE_RVA(Addresses::GameStartData::GetGameID);

	return x64RetSpoof::spoof_call(fn, this);
}

uint64_t GameStartData::get_region()
{
	typedef uint64_t(__fastcall* fnGetRegion)(GameStartData*);
	static fnGetRegion fn = (fnGetRegion)MAKE_RVA(Addresses::GameStartData::GetRegion);

	return x64RetSpoof::spoof_call(fn, this);
}

const char* GameStartData::get_game_type()
{
	const char* str = RVA_CAST_THIS(const char*, Structures::GameStartData::GameType);

	if (!str || !Utils::is_valid_string(str))
		return "";

	return str;
}

const char* GameStartData::get_player_ip()
{
	const char* str = RVA_CAST_THIS(const char*, Structures::GameStartData::PlayerIp);

	if (!str || !Utils::is_valid_string(str))
		return "";

	return str;
}

const char* GameStartData::get_game_name()
{
	const char* str = RVA_CAST_THIS(const char*, Structures::GameStartData::GameName);

	if (!str || !Utils::is_valid_string(str))
		return "";

	return str;
}