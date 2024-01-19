#include "../pch.h"
#include "HooksCommons.h"
#include "../Impl/Base/base.h"

namespace Process
{
#define ROR(x, y) ((unsigned)(x) >> (y) | (unsigned)(x) << 32 - (y))

	typedef
	enum _PROCESSINFOCLASS
	{
		ProcessBasicInformation,
		ProcessCookie = 36
	} PROCESSINFOCLASS;

	extern "C" NTSYSCALLAPI NTSTATUS NTAPI NtQueryInformationProcess(IN HANDLE ProcessHandle,
		IN PROCESSINFOCLASS ProcessInformationClass,
		OUT PVOID ProcessInformation,
		IN ULONG ProcessInformationLength,
		OUT PULONG ReturnLength OPTIONAL);

	static uintptr_t process_cookie_ = 0;

	uintptr_t GetProcessCookie()
	{
		uintptr_t dwProcessCookie = NULL;
		NTSTATUS NtStatus = NtQueryInformationProcess(GetCurrentProcess(), ProcessCookie, &dwProcessCookie, 4, nullptr);

		if (!NT_SUCCESS(NtStatus))
			return NULL;

		return dwProcessCookie;
	}

	uintptr_t DecodePointerHandle(uintptr_t pointer)
	{
		if (!process_cookie_)
		{
			process_cookie_ = GetProcessCookie();
			if (!process_cookie_)
			{
				return 0;
			}
		}

		unsigned char shift_size = 0x20 - (process_cookie_ & 0x1f);
		return ROR(pointer, shift_size) ^ process_cookie_;
	}

	uintptr_t GetVEHOffset()
	{
		//HMODULE ntdll = GetModuleHandleA("ntdll.dll");

		//const char* sig_str = "89 46 10 81 C3 ?? ?? ?? ??";

		//uintptr_t match_list = (uintptr_t) base::find_pattern("ntdll.dll", sig_str);
		//BYTE* veh_list = *reinterpret_cast<BYTE**>(match_list + 5);
		//size_t veh_list_offset = veh_list - reinterpret_cast<BYTE*>(ntdll);

		//return veh_list_offset;

		return 0;
	}

	_VECTORED_HANDLER_LIST* GetVECTORED_HANDLER_LIST(uintptr_t& veh_addr)
	{
		uintptr_t ntdll = (uintptr_t)GetModuleHandleA(skCrypt("ntdll.dll"));
		_VECTORED_HANDLER_LIST* handler_list;
		uintptr_t VEHOffset = GetVEHOffset();
		veh_addr = ntdll + VEHOffset;
		handler_list = &*(_VECTORED_HANDLER_LIST*)veh_addr;

		return handler_list;
	}

	std::vector<PVECTORED_EXCEPTION_HANDLER> getAllHandlers()
	{
		std::vector<PVECTORED_EXCEPTION_HANDLER> _PVECTORED_EXCEPTION_HANDLER_list;

		uintptr_t veh_addr;
		_VECTORED_HANDLER_LIST* handler_list = GetVECTORED_HANDLER_LIST(veh_addr);

		VECTORED_HANDLER_ENTRY* entry;
		entry = &*(VECTORED_HANDLER_ENTRY*)((uintptr_t)handler_list->first_exception_handler);

		while (true)
		{
			uintptr_t handler = reinterpret_cast<uintptr_t>(entry->handler);
			_PVECTORED_EXCEPTION_HANDLER_list.push_back((PVECTORED_EXCEPTION_HANDLER)(DecodePointerHandle(handler)));

			if (reinterpret_cast<uintptr_t>(entry->next) == veh_addr + sizeof(uintptr_t))
			{
				break;
			}
			entry = &*(VECTORED_HANDLER_ENTRY*)((uintptr_t)entry->next);
		}
		return _PVECTORED_EXCEPTION_HANDLER_list;
	}

	void removeAllHandlers()
	{
		HMODULE ntdll = GetModuleHandleA("ntdll.dll");

		uintptr_t remove_exception_handler = reinterpret_cast<uintptr_t>(GetProcAddress(ntdll, skCrypt("RtlRemoveVectoredExceptionHandler"))
			);


		typedef BOOL(__stdcall* t_RemoveVectoredExceptionHandler)(PVOID Handle);
		t_RemoveVectoredExceptionHandler fn_RemoveVectoredExceptionHandler = (t_RemoveVectoredExceptionHandler)remove_exception_handler;

		for (int i = 0; i < getAllHandlers().size(); i++)
		{
			uintptr_t veh_addr;
			_VECTORED_HANDLER_LIST* handler_list = GetVECTORED_HANDLER_LIST(veh_addr);
			fn_RemoveVectoredExceptionHandler(static_cast<PVOID>(handler_list->first_exception_handler));
		}
	}

	void reAddAllHandlers(std::vector<PVECTORED_EXCEPTION_HANDLER> handlerList)
	{
		for (PVECTORED_EXCEPTION_HANDLER pvh : handlerList)
		{
			AddVectoredExceptionHandler(0, pvh);
		}
	}
}
