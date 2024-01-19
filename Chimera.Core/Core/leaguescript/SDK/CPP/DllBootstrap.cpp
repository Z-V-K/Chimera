#include "../pch.h"
#include "DllBootstrap.h"

#include "DllMapper.h"
#include "../SDK/CPP/PluginSDK.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Logger/Logger.h"
#include "../Impl/Common/Utils.h"

typedef bool(__cdecl* DllEntry)(SDK::PluginSDK* pluginSDK);

const std::string dllPath = g_ctx->plugins_path;
const std::string tmpDllPath = dllPath + "tmp/";

std::filesystem::path move_file(std::filesystem::directory_entry file)
{
	// create tmp/ folder if it doesnt exist.
	if (!std::filesystem::exists(tmpDllPath))
	{
		std::filesystem::create_directory(tmpDllPath);
	}
	
	std::filesystem::path newFile = std::filesystem::path(tmpDllPath + file.path().filename().string());

	std::filesystem::copy_file(file.path(), newFile);

	return newFile;
}

uint32_t generate_error(uint32_t exceptionCode, LPEXCEPTION_POINTERS ex, const std::filesystem::path& filePath)
{
	char buff[256];
	sprintf(buff,
		xorstr_("%s: Exception triggered.\nAddr: 0x%llx\nCode: 0x%llX\nRIP: 0x%llX\nRAX: 0x%llX\nRBX: 0x%llX\nRCX: 0x%llX\nRDX: 0x%llX"),
		xorstr_("on_sdk_load"),
		(uintptr_t)ex->ExceptionRecord->ExceptionAddress,
		(uintptr_t)exceptionCode,
		(uintptr_t)ex->ContextRecord->Rip,
		(uintptr_t)ex->ContextRecord->Rax,
		(uintptr_t)ex->ContextRecord->Rbx,
		(uintptr_t)ex->ContextRecord->Rcx,
		(uintptr_t)ex->ContextRecord->Rdx
	);

	Log::error(buff);

	return EXCEPTION_EXECUTE_HANDLER;
}

void DllBootstrap::delete_dlls()
{
	const auto hProc = GetCurrentProcess();

	for (const auto& script : registered_scripts)
	{
		script.second->sdk_unload();

#ifdef PROD
		VirtualFreeEx(hProc, (LPVOID) script.first, 0, MEM_RELEASE);
#else
		FreeLibrary(script.first);
#endif
	}

#ifndef PROD
	if(std::filesystem::exists(tmpDllPath))
	{
		// delete all files in tmp/
		for (const auto& file : std::filesystem::directory_iterator(tmpDllPath))
		{
			if (file.path().extension() == xorstr_(".dll"))
			{
				std::filesystem::remove(file);
			}
		}
	}
#endif

	CloseHandle(hProc);
	registered_scripts.clear();
}

bool load_dll(on_sdk_load on_sdk_load, const std::filesystem::path& file_path)
{
	__try
	{
		return on_sdk_load(SDK::exported_plugin_sdk);
	}
	__except (generate_error(GetExceptionCode(), GetExceptionInformation(), file_path))
	{
		return false;
	}
}

void DllBootstrap::execute_dll(const std::filesystem::path& file_path)
{
#ifdef PROD
	const auto script_data = DllMapper::get().map_dll(file_path.string().c_str());
	const auto script = script_data.second;

	if (!script_data.first || !script->initialized)
		return;

	if (!script->sdk_load || !script->sdk_unload || script->name.empty() || script->supported_champions.empty())
	{
		g_ctx->mConsole->log_error(xorstr_("Please declare exported fields/functions properly in %s"), file_path.filename().string().c_str());
		const auto hProc = GetCurrentProcess();
		VirtualFreeEx(hProc, (LPVOID)script_data.first, 0, MEM_RELEASE);
		CloseHandle(hProc);
		return;
	}

	bool supported = false;

	for (const auto& champ : script->supported_champions)
	{
		if (champ == 0x0 || champ == GameObject::get_local_player()->get_character_hash())
			supported = true;
	}

	if (!supported)
	{
		const auto hProc = GetCurrentProcess();
		VirtualFreeEx(hProc, (LPVOID)script_data.first, 0, MEM_RELEASE);
		CloseHandle(hProc);
		return;
	}

	if (load_dll(script->sdk_load, file_path))
	{
		registered_scripts.insert(script_data);
	}
#endif
}

void DllBootstrap::load_library_dll(const std::filesystem::path& file_path)
{
#ifndef PROD
	HINSTANCE handle{ LoadLibrary(file_path.c_str()) };

	if (!handle)
		return;

	const auto script_name = (const std::string*) GetProcAddress(handle, xorstr_("script_name"));
	const auto script_type = (ScriptType*)GetProcAddress(handle, xorstr_("script_type"));
	const auto script_champions = (std::vector<uint32_t>*)GetProcAddress(handle, xorstr_("script_champions"));
	const auto sdk_load = (on_sdk_load) GetProcAddress(handle, xorstr_("on_load_sdk"));
	const auto sdk_unload = (on_sdk_unload) GetProcAddress(handle, xorstr_("on_unload_sdk"));

	if (!sdk_load || !sdk_unload || !script_name || !script_type || !script_champions)
	{
		g_ctx->mConsole->log_error(xorstr_("Please declare exported fields/functions properly in %s"), file_path.filename().string().c_str());
		FreeLibrary(handle);
		return;
	}

	bool is_champ_supported = false;

	for (const auto& champ : *script_champions)
	{
		if (champ == 0x0 || GameObject::get_local_player()->get_character_hash() == champ)
		{
			is_champ_supported = true;
			break;
		}
	}

	if (!is_champ_supported)
	{
		FreeLibrary(handle);
		return;
	}

	if (load_dll(sdk_load, file_path))
	{
		registered_scripts.insert({
			handle,
			std::make_shared<Script>(true, *script_name, *script_type, *script_champions, (on_sdk_load)sdk_load, (on_sdk_unload)sdk_unload)
		});
	}
#endif
}

void DllBootstrap::load_dlls()
{
#ifndef PROD
	// ensure there are no entries in tmp/ folder.
	delete_dlls();
#endif

	for (const auto& file : std::filesystem::directory_iterator(dllPath))
	{
		// ignore all non .dll files
		if (file.path().extension() != xorstr_(".dll"))
			continue;

#ifdef PROD
		execute_dll(file);
#else
		const auto dll = move_file(file);
		load_library_dll(dll);
#endif
	}
}

void DllBootstrap::reload_dlls()
{
	clock_t start, end;
	start = clock();

	delete_dlls();
	load_dlls();

	end = clock();
	g_ctx->mConsole->log_info(xorstr_("Reloaded scripts after %.3fs"), double(end - start) / 1000);
}