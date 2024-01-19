#pragma once

#include "../Impl/UI/Console/Console.h"
#include "../Impl/Hooks/syscall/syscall.h"

#define LOG(...) g_ctx->mConsole->log_debug(__VA_ARGS__);

class Menu;

class Context
{
public:
	HMODULE mDll = nullptr;
	bool unload = false;

	bool mInitializedUI = false;
	
	uintptr_t mModuleBase;

	std::shared_ptr<Console> mConsole;

	inline_syscall syscall{ };

	std::string get_root_path();

	std::string config_path = get_root_path() + std::string(skCrypt("config.json"));
	std::string plugins_path = get_root_path() + std::string(skCrypt("Plugins\\"));
	std::string cache_path = get_root_path() + std::string(skCrypt("Cache\\"));
	std::string shader_path = get_root_path() + std::string(skCrypt("Shaders\\"));
	std::string pixel_shader_path = get_root_path() + std::string(skCrypt("Shaders\\ps.hlsl"));
	std::string vertex_shader_path = get_root_path() + std::string(skCrypt("Shaders\\vs.hlsl"));

	std::string images_path = cache_path + std::string(skCrypt("Images\\"));
#ifdef __DEV
	bool mShowConsole = true;
	bool mShowConsoleAlways = true;
#else
	bool mShowConsole = false;
	bool mShowConsoleAlways = false;
#endif
};

extern Context* g_ctx;