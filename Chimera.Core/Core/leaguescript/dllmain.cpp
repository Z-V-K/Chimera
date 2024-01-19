#include "../pch.h"
#include "../Core/Core.h"
#include "../Core/Context/Context.h"
#include "../Framework/GameClient/GameClient.h"

void CreateConsole()
{
    if (!AllocConsole()) {
        return;
    }
    freopen(xorstr_("CONIN$"), xorstr_("r"), stdin);
    freopen(xorstr_("CONOUT$"), xorstr_("w"), stdout);
    freopen(xorstr_("CONOUT$"), xorstr_("w"), stderr);
}

void on_attach(HMODULE hModule)
{
    g_ctx->mDll = hModule;
    m_core = std::make_shared<Core>();
    m_core->run();

    while (!g_ctx->unload && GameClient::instance()->get_game_state() != Enums::GameState::Finished)
        Sleep(1000);

    m_core->unload();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    UNREFERENCED_PARAMETER(lpReserved);
    DisableThreadLibraryCalls(hModule);

    switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)on_attach, hModule, NULL, NULL);
        break;
    default:
        break;
    }

    return TRUE;
}