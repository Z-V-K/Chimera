#include "../pch.h"
#include "Core.h"

#include "../Core/Context/Context.h"
#include "../Impl/Hooks/Decrypt/Decrypt.h"
#include "../Impl/Hooks/Hook.h"
#include "../Impl/Hooks/Inline/InlineHook.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Impl/Hooks/syscall/syscall.h"
#include "../Impl/Logger/Logger.h"
#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Impl/Managers/EventManager/EventManager.h"
#include "../Impl/Managers/ConfigManager/ConfigManager.h"
#include "../Impl/Globals/Globals.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"
#include "../SDK/CPP/DllBootstrap.h"
#include "../Impl/EntityList/EntityList.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Framework/Hud/Zoom/Zoom.h"
#include "../Framework/GameEngine/EventSystem/EventSystem.h"
#include "../Framework/GameClient/GameClient.h"
#include "../Impl/Bypass/Bypass.h"
#include "../Impl/Common/Utils.h"
#include "../SDK/CPP/PluginSDK.h"
#include "../SDK/LUA/LuaBootstrap.h"

#define VERIFY_HOOK( CLASS, NAME) if (!CLASS::apply_hooks()) { Log::error(skCrypt("[!] %s Hooks Failed!"), #CLASS); return false; }

std::shared_ptr<Core> m_core;

void InitThread();

void createFolders()
{
	if (!std::filesystem::exists(g_ctx->get_root_path()))
		std::filesystem::create_directory(g_ctx->get_root_path());

	if (!std::filesystem::exists(g_ctx->plugins_path))
		std::filesystem::create_directory(g_ctx->plugins_path);

	if (!std::filesystem::exists(g_ctx->cache_path))
		std::filesystem::create_directory(g_ctx->cache_path);

	if (!std::filesystem::exists(g_ctx->images_path))
		std::filesystem::create_directory(g_ctx->images_path);

	if (!std::filesystem::exists(g_ctx->shader_path))
		std::filesystem::create_directory(g_ctx->shader_path);
}

Core::Core() : m_hookManager(nullptr)
{
	g_ctx->mModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
	g_ctx->mConsole = std::make_shared<Console>();
	g_ctx->syscall = inline_syscall{ };
	m_hookManager = std::make_shared<HookManager>();
	x64RetSpoof::initialize();
	Log::init();
	createFolders();
}

void Core::run()
{
	while (GameClient::instance()->get_game_state() != Enums::GameState::Running && !GameObject::get_local_player())
		Sleep(10);

	if (!Globals::is_script_version_latest())
	{
		MessageBoxA(nullptr, skCrypt("Error code: 0x0"), skCrypt("Outdated core!"), 0);
		g_ctx->unload = true;
		return;
	}

	MenuManager::init_menu();

	if (!apply_hooks()) {
		Log::error(skCrypt("[!] Failed to apply Core hooks"));
		return;
	}
	
	m_core->load_features();
	g_config_manager->load_config();
}

std::shared_ptr<HookManager> Core::get_hook_manager() const {
	return m_hookManager;
}

bool Core::apply_hooks() const
{
	if (!m_hookManager) {
		return false;
	}

	InlineHook::initialize();

	VERIFY_HOOK(r3dRenderer, skCrypt("r3dRenderer"))
	VERIFY_HOOK(GameObject, skCrypt("GameObject"))
	VERIFY_HOOK(Spellbook, skCrypt("Spellbook"))
	VERIFY_HOOK(EventSystem, skCrypt("EventSystem"))

	return true;
}

void Core::load_features() const
{
	g_entityList->initialize();

	DllBootstrap::load_dlls();
	LuaBootstrap::load_scripts();
}

void Core::unload() const
{
	Zoom::set_max_zoom(600.f);
	Zoom::set_camera_angle(40.f);
	g_event_manager->clear_events();
	m_hookManager->unload_hooks();
	Log::un_init();
	DllBootstrap::delete_dlls();
	delete SDK::exported_plugin_sdk;

	Sleep(1000);

#ifdef PROD
	HANDLE hProc = GetCurrentProcess();
	VirtualFreeEx(hProc, (PVOID)g_ctx->mDll, 0, MEM_RELEASE);
	CloseHandle(hProc);
#else
	FreeLibraryAndExitThread(g_ctx->mDll, NULL);
#endif
}