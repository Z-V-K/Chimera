#include "../pch.h"
#include "InlineHook.h"

#include "../Addresses/Addresses.h"
#include "../Impl/Hooks/syscall/syscall.h"
#include "../Impl/Hooks/Decrypt/Decrypt.h"
#include "../Core/Context/Context.h"
#include "../Impl/Common/Common.h"
#include "../Impl/Logger/Logger.h"

#include "../Impl/Base/base.h"

namespace InlineHook
{
    void sys_VirtualProtect(LPVOID lpAddress, SIZE_T* dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) {
        g_ctx->syscall.invoke<NTSTATUS>(skCrypt("ZwProtectVirtualMemory"), GetCurrentProcess(), lpAddress, dwSize, flNewProtect, lpflOldProtect);
    }

    void initialize()
    {
        load_hashes();
    }

    void remove(uintptr_t ogPageAddr, uintptr_t og_addr, const std::vector<byte>& ogBytes)
    {
        uintptr_t shadowFnAddr = get_addr_from_shadow_module(og_addr);

        DWORD dwOld;
        size_t tmpsize = ogBytes.size();
        sys_VirtualProtect((void*) shadowFnAddr, &tmpsize, PAGE_EXECUTE_READWRITE, &dwOld);

        for (size_t i = 0; i < ogBytes.size(); i++)
        {
            byte* bytes = (byte*) shadowFnAddr;
            *(bytes + i) = ogBytes[i];
        }

        tmpsize = ogBytes.size();
        sys_VirtualProtect((void*)shadowFnAddr, &tmpsize, dwOld, &dwOld);

        if (hashes.contains(ogPageAddr))
			hashes[ogPageAddr].restore_hash();
    }

    bool get_shadow_module(uintptr_t& base_address)
    {
        MEMORY_BASIC_INFORMATION64 mbi = { 0 };
        DWORD64 start = 0;
        DWORD64 result = 0;
        while (VirtualQuery(reinterpret_cast<LPVOID>(start), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&mbi), sizeof(MEMORY_BASIC_INFORMATION64)) != 0)
        {
            if (mbi.Protect & PAGE_READWRITE && mbi.State == MEM_COMMIT && mbi.Type == 0x40000)
            {
                result = (DWORD64)mbi.AllocationBase;
                if (*reinterpret_cast<WORD*>(result) == 0x5A4D)
                {
                    const PIMAGE_NT_HEADERS64 ntPtr = reinterpret_cast<PIMAGE_NT_HEADERS64>(result + reinterpret_cast<PIMAGE_DOS_HEADER>(result)->e_lfanew);
                    if (ntPtr->FileHeader.NumberOfSections == 10)
                        break;
                }
            }

            start += mbi.RegionSize;
        }
        base_address = result;
        return true;
    }

    int get_league_nb_pages()
    {
        MODULEINFO moduleinfo;
        GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &moduleinfo, sizeof moduleinfo);

        return moduleinfo.SizeOfImage / 0x1000;
    }

    void load_hashes()
    {
        uintptr_t shadowModule;
        get_shadow_module(shadowModule);

        if (!shadowModule)
            return;

        const uintptr_t leagueModule = (uintptr_t)GetModuleHandleA(nullptr);
        const uint32_t* arrayRelativeAddr = (uint32_t*) (base::find_pattern(skCrypt("stub.dll"), skCrypt("48 8D 05 ? ? ? ? 42 33 8C 28 ? ? ? ?")) + 0x3);
        const uintptr_t arrayAddr = ((uintptr_t) arrayRelativeAddr + *arrayRelativeAddr) + 0x4;

        const uint32_t structSize = 0x108;

        const int nbPages = get_league_nb_pages();
        for (int i = 4; i <= nbPages; i++)
        {
            hash_struct* hash = reinterpret_cast<hash_struct*>(arrayAddr + i * structSize);

            hashes.insert({ leagueModule + 0x1000 * i, section_hash(hash) });
        }
    }

    void replace_hash(uintptr_t func_address, uintptr_t* og_page_addr)
    {
        int nb_pages = get_league_nb_pages();
        uintptr_t league = (uintptr_t)GetModuleHandleA(nullptr);

        for (int i = 4; i <= nb_pages; i++)
        {
            uintptr_t curr_page = league + 0x1000 * i;
            uintptr_t next_page = league + 0x1000 * (i + 1);

            if (func_address < curr_page || func_address > next_page)
                continue;

            *og_page_addr = curr_page;

            if (hashes.contains(curr_page))
				hashes[curr_page].bypass_hash();
        }
    }

    uintptr_t get_addr_from_shadow_module(uintptr_t addr)
    {
        uintptr_t shadow_module = 0;
        get_shadow_module(shadow_module);

        std::uintptr_t league_base = (uintptr_t)GetModuleHandle(nullptr);

        uintptr_t offset = addr - league_base;
        uintptr_t address = (shadow_module + offset);

        return address;
    }

    uintptr_t hook(void* src, void* dest, size_t size, std::vector<byte>* ogBytes, uintptr_t* og_page_addr)
    {
        DWORD MinLen = 14;

        if (size < MinLen) return NULL;

        BYTE stub[] = {
	        0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
	        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
        };

        for (int i = 0; i < size; i++)
        {
            ogBytes->push_back(*(uint8_t*)((uintptr_t) src + i));
        }

        BYTE* address = (BYTE*) get_addr_from_shadow_module((uintptr_t) src);

        void* pTrampoline = VirtualAlloc(0, size + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        DWORD dwOld = 0;

        size_t tmpsize = size;
        sys_VirtualProtect(address, &tmpsize, PAGE_EXECUTE_READWRITE, &dwOld);

        DWORD64 retto = (DWORD64)src + size;

        // trampoline
        memcpy(stub + 6, &retto, 8);
        memcpy((void*)((DWORD_PTR)pTrampoline), src, size);
        memcpy((void*)((DWORD_PTR)pTrampoline + size), stub, sizeof(stub));

        // orig
        memcpy(stub + 6, &dest, 8);
        memcpy(address, stub, sizeof(stub));

        for (int i = MinLen; i < size; i++)
        {
            *(BYTE*)((DWORD_PTR)address + i) = 0x90;
        }

        tmpsize = size;
        sys_VirtualProtect(address, &tmpsize, dwOld, &dwOld);

        replace_hash((uintptr_t)src, og_page_addr);

        return (uintptr_t) pTrampoline;
    }
}
