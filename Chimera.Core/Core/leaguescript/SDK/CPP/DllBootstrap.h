#pragma once
#include "Script.h"

class DllBootstrap
{
public:
	static void execute_dll(const std::filesystem::path& file_path);
	static void load_library_dll(const std::filesystem::path& file_path);
	static void load_dlls();
	static void reload_dlls();
	static void delete_dlls();

#ifdef PROD
	inline static std::map<uintptr_t, std::shared_ptr<Script>> registered_scripts{ };
#else
	inline static std::map<HINSTANCE, std::shared_ptr<Script>> registered_scripts{ };
#endif
};
