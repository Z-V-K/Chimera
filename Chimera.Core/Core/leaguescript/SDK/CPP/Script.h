#pragma once

namespace SDK
{
	class PluginSDK;
}

enum class ScriptType
{
	Champion,
	Prediction,
	Evade,
	Orbwalker,
	Utility,
	Misc,
	Core
};

typedef bool(__fastcall* on_sdk_load)(SDK::PluginSDK*);
typedef void(__fastcall* on_sdk_unload)();

struct Script
{
	bool initialized = false;
	
	std::string name;
	ScriptType type;
	std::vector<uint32_t> supported_champions;

	on_sdk_load sdk_load = nullptr;
	on_sdk_unload sdk_unload = nullptr;
};