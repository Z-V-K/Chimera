#pragma once

#include "../Core/Core.h"

enum class convention_type {
    stdcall_t,
    cdecl_t,
    thiscall_t,
    fastcall_t,
};

template < convention_type tp, typename retn, typename ...args >
struct convention;

template < typename retn, typename ...args >
struct convention< convention_type::stdcall_t, retn, args... > {
    typedef retn(__stdcall* type)(args ...);
};

template < typename retn, typename ...args >
struct convention< convention_type::cdecl_t, retn, args... > {
    typedef retn(__cdecl* type)(args ...);
};

template < typename retn, typename ...args >
struct convention< convention_type::thiscall_t, retn, args... > {
    typedef retn(__thiscall* type)(args ...);
};

template < typename retn, typename ...args >
struct convention< convention_type::fastcall_t, retn, args... > {
    typedef retn(__fastcall* type)(args ...);
};

struct HookEntry {
    void* m_original;
    void* m_target;
    void* m_detour;

    std::vector<byte> ogJmpBytes;
    uintptr_t ogPageAddr;

    HookEntry(void* original, void* target, void* detour) : m_original(original), m_target(target), m_detour(detour) {
    }
};

class HookManager {

private:
    std::vector< HookEntry > m_hookList;
    std::vector< HookEntry > m_jmpHookList;

public:
    void* install(void* target, void* detour);
    void* install_jmp(void* target, void* detour, size_t size);
    bool  unload_hooks() const;
};

template < convention_type tp = convention_type::cdecl_t, typename retn = void, typename ...args >
class Hook {

private:
    bool m_isApplied;

public:
    typedef typename convention< tp, retn, args... >::type type;

    type m_original;
    type m_detour;

    Hook() : m_isApplied(false), m_original(nullptr), m_detour(nullptr) {
    }

    template < typename T >
    Hook(T func, type detour) {
        apply< T >(func, detour);
    }

    template < typename T >
    void apply(T func, type detour) {
        if (m_isApplied) {
            return;
        }

        m_detour = detour;
        m_original = reinterpret_cast<type>(m_core->get_hook_manager()->install(reinterpret_cast<void*>(func), reinterpret_cast<void*>(detour)));
        if (m_original) {
            m_isApplied = true;
        }
    }

    template < typename T >
    void apply_jmp(T func, DWORD64 detour, size_t size) {
        if (m_isApplied) {
            return;
        }

        m_original = reinterpret_cast<type>(m_core->get_hook_manager()->install_jmp(reinterpret_cast<void*>(func), reinterpret_cast<void*>(detour), size));
        if (m_original) {
            m_isApplied = true;
        }
    }

    template < typename T >
    void apply_hwbp(T func, DWORD64 detour, uint8_t registerIndex, size_t functionSize) {
        //if (m_isApplied) {
        //    return;
        //}

        //m_original = reinterpret_cast<type>(m_core->get_hook_manager()->installHWBP(reinterpret_cast<void*>(func), reinterpret_cast<void*>(detour), registerIndex, functionSize));
        //if (m_original) {
        //    m_isApplied = true;
        //}
    }

    template < typename T >
    void apply_veh(T func, DWORD64 detour, size_t offset, size_t functionSize) {
        //if (m_isApplied) {
        //    return;
        //}

        //m_original = reinterpret_cast<type>(m_core->get_hook_manager()->installVEH(reinterpret_cast<void*>(func), reinterpret_cast<void*>(detour), offset, functionSize));
        //if (m_original) {
        //    m_isApplied = true;
        //}
    }

    retn call_original(args ... p) {
        return m_original(p...);
    }

    retn call_detour(args ... p) {
        return m_detour(p...);
    }

    bool is_applied() const {
        return m_isApplied;
    }
};
