#include "../pch.h"
#include "../Impl/Hooks/Hook.h"

#include "../Core/Context/Context.h"
#include "../Impl/Logger/Logger.h"
#include "../Impl/Hooks/Inline/InlineHook.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"
#include "../Impl/Hooks/Decrypt/Decrypt.h"

void* HookManager::install(void* target, void* detour) {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    PDETOUR_TRAMPOLINE trampoline;
    DetourAttachEx(&target, detour, &trampoline, nullptr, nullptr);
    if (const auto error = DetourTransactionCommit() != NO_ERROR) {
        Log::error(skCrypt("hook install 0x%p failed - error %i"), target, error);
    }
    if (trampoline) {
        m_hookList.push_back(HookEntry(trampoline, target, detour));
    }

    return trampoline;
}

void* HookManager::install_jmp(void* target, void* detour, size_t size)
{
    std::vector<byte> ogBytes{ };
    uintptr_t ogPageAddr{ };

    LeagueDecrypt::decrypt((uintptr_t)target);

    uintptr_t retAddr = InlineHook::hook(target, detour, size, &ogBytes, &ogPageAddr);
    HookEntry hookEntry{ (PVOID)retAddr, target, detour };

    hookEntry.ogJmpBytes = ogBytes;
    hookEntry.ogPageAddr = ogPageAddr;

    m_jmpHookList.push_back(hookEntry);

    return (PVOID)retAddr;
}

bool HookManager::unload_hooks() const {

    r3dRenderer::remove_hwnd_hook();

    for (auto hookEntry : m_hookList)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&hookEntry.m_original, hookEntry.m_detour);
        if (const auto error = DetourTransactionCommit() != NO_ERROR) {
            MessageBoxA(nullptr, skCrypt("unhook fail"), skCrypt("unhook fail"), MB_OK);
            Log::error(skCrypt("hook unload 0x%p failed - error %i"), hookEntry.m_original, error);
        }
    }

    for (const auto& hookEntry : m_jmpHookList)
    {
        InlineHook::remove(hookEntry.ogPageAddr, (uintptr_t)hookEntry.m_target, hookEntry.ogJmpBytes);
        VirtualFree(hookEntry.m_original, 0, MEM_RELEASE);
    }

    return true;
}