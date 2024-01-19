#include "DllMapper.h"

#define CURRENT_ARCH IMAGE_FILE_MACHINE_AMD64
#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef PROD
#define console_print(...)
#else
#define console_print(...) printf(__VA_ARGS__);
#endif

void __stdcall Shellcode(MANUAL_MAPPING_DATA* pData, Script& script_data);
Script ManualMapDll(HANDLE hProc, BYTE* pSrcData, uintptr_t* pBase);

std::vector<uint8_t> key = {
	0xc9, 0x10, 0x8f, 0x7f, 0x75, 0x05, 0xf9, 0x5f, 0x2e, 0x37, 0xcb, 0xdf, 0x18, 0x82, 0x29, 0xd1,
	0xcd, 0x17, 0x5c, 0x61, 0x70, 0x79, 0x79, 0x37, 0xc5, 0xd7, 0x9d, 0x1d, 0xa9, 0xe2, 0x40, 0xc6,
	0x51, 0x2f, 0x80, 0x07, 0xd8, 0xbf, 0xab, 0x47, 0x44, 0x82, 0x1c, 0xd8, 0x21, 0x3f, 0xd6, 0xe2,
	0x6f, 0xa9, 0x29, 0x0a, 0x73, 0xc6, 0xbe, 0xf4, 0xf8, 0xeb, 0xb8, 0xb7, 0xdd, 0xa6, 0xc0, 0xe5,
	0x5b, 0x35, 0x08, 0x56, 0x15, 0xf9, 0x26, 0xe3, 0xa1, 0x96, 0x0d, 0x5f, 0xed, 0x80, 0xc0, 0x2b,
	0x07, 0x80, 0x24, 0x3f, 0x89, 0x3e, 0x6b, 0x89, 0xd9, 0x00, 0x59, 0x81, 0x64, 0xb6, 0xb3, 0xc6,
	0x77, 0xa1, 0x08, 0x72, 0xf3, 0x1e, 0x9c, 0xd0, 0xcd, 0xba, 0x55, 0xa1, 0xcc, 0x63, 0x4a, 0x89,
};

BYTE* get_decrypted_dll(BYTE* original, std::streampos fileSize)
{
	size_t key_idx = 0;

	for (unsigned long long i = 0; i < (UINT_PTR)fileSize; i++)
	{
		original[i] ^= key[key_idx];
		key_idx = (key_idx + 1) % (key.size() - 1);
	}

	return original;
}

std::pair<uintptr_t, std::shared_ptr<Script>> DllMapper::map_dll(const char* dll_path)
{
	const char* dllPath = dll_path;

	TOKEN_PRIVILEGES priv = { 0 };
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		priv.PrivilegeCount = 1;
		priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &priv.Privileges[0].Luid))
			AdjustTokenPrivileges(hToken, FALSE, &priv, 0, NULL, NULL);

		CloseHandle(hToken);
	}

	HANDLE hProc = GetCurrentProcess();
	if (!hProc) {
		DWORD Err = GetLastError();
		console_print(xorstr_("OpenProcess failed: 0x%X\n"), Err);
		return { };
	}

	std::ifstream File(dllPath, std::ios::binary | std::ios::ate);

	if (File.fail()) {
		console_print(xorstr_("Opening the file failed: %X\n"), (DWORD)File.rdstate());
		File.close();
		CloseHandle(hProc);
		return { };
	}

	auto FileSize = File.tellg();
	if (FileSize < 0x1000) {
		console_print(xorstr_("Filesize invalid.\n"));
		File.close();
		CloseHandle(hProc);
		return { };
	}

	BYTE* pSrcData = new BYTE[(UINT_PTR)FileSize];
	if (!pSrcData) {
		console_print(xorstr_("Can't allocate dll file.\n"));
		File.close();
		CloseHandle(hProc);
		return { };
	}

	File.seekg(0, std::ios::beg);
	File.read((char*)(pSrcData), FileSize);
	File.close();

	pSrcData = get_decrypted_dll(pSrcData, FileSize);

	console_print(xorstr_("Mapping...\n"));
	uintptr_t pBase = 0;
	Script script = ManualMapDll(hProc, pSrcData, &pBase);

	if (!script.initialized)
	{
		delete[] pSrcData;
		CloseHandle(hProc);
		console_print(xorstr_("Error while mapping.\n"));
		return { };
	}

	delete[] pSrcData;

	CloseHandle(hProc);
	return { pBase, std::make_shared<Script>(script) };
}

bool DllMapper::unmap_dll(const char* dll_path)
{
	return true;
}

Script ManualMapDll(HANDLE hProc, BYTE* pSrcData, uintptr_t* pBase) {
	IMAGE_NT_HEADERS* pOldNtHeader = nullptr;
	IMAGE_OPTIONAL_HEADER* pOldOptHeader = nullptr;
	IMAGE_FILE_HEADER* pOldFileHeader = nullptr;
	BYTE* pTargetBase = nullptr;

	if (reinterpret_cast<IMAGE_DOS_HEADER*>(pSrcData)->e_magic != 0x5A4D) { //"MZ"
		console_print(xorstr_("Invalid file\n"));
		return { };
	}

	pOldNtHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(pSrcData + reinterpret_cast<IMAGE_DOS_HEADER*>(pSrcData)->e_lfanew);
	pOldOptHeader = &pOldNtHeader->OptionalHeader;
	pOldFileHeader = &pOldNtHeader->FileHeader;

	if (pOldFileHeader->Machine != CURRENT_ARCH) {
		console_print(xorstr_("Invalid platform\n"));
		return { };
	}

	console_print("File ok\n");

	pTargetBase = reinterpret_cast<BYTE*>(VirtualAllocEx(hProc, nullptr, pOldOptHeader->SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
	if (!pTargetBase) {
		console_print(xorstr_("Target process memory allocation failed (ex) 0x%X\n"), GetLastError());
		return { };
	}

	DWORD oldp = 0;
	VirtualProtectEx(hProc, pTargetBase, pOldOptHeader->SizeOfImage, PAGE_EXECUTE_READWRITE, &oldp);

	MANUAL_MAPPING_DATA data{ 0 };
	data.pLoadLibraryA = LoadLibraryA;
	data.pGetProcAddress = GetProcAddress;
	data.pRtlAddFunctionTable = (f_RtlAddFunctionTable)RtlAddFunctionTable;
	data.pbase = pTargetBase;
	data.fdwReasonParam = DLL_PROCESS_ATTACH;
	data.reservedParam = nullptr;
	data.SEHSupport = true;


	//File header
	if (!WriteProcessMemory(hProc, pTargetBase, pSrcData, 0x1000, nullptr)) { //only first 0x1000 bytes for the header
		console_print(xorstr_("Can't write file header 0x%X\n"), GetLastError());
		VirtualFreeEx(hProc, pTargetBase, 0, MEM_RELEASE);
		return { };
	}

	IMAGE_SECTION_HEADER* pSectionHeader = IMAGE_FIRST_SECTION(pOldNtHeader);
	for (UINT i = 0; i != pOldFileHeader->NumberOfSections; ++i, ++pSectionHeader) {
		if (pSectionHeader->SizeOfRawData) {
			if (!WriteProcessMemory(hProc, pTargetBase + pSectionHeader->VirtualAddress, pSrcData + pSectionHeader->PointerToRawData, pSectionHeader->SizeOfRawData, nullptr)) {
				console_print(xorstr_("Can't map sections: 0x%x\n"), GetLastError());
				VirtualFreeEx(hProc, pTargetBase, 0, MEM_RELEASE);
				return { };
			}
		}
	}

	console_print(xorstr_("Mapped DLL at %p\n"), pTargetBase);
	console_print(xorstr_("Data allocated\n"));

	Script script{ };
	Shellcode(&data, script);

	BYTE* emptyBuffer = (BYTE*)malloc(1024 * 1024 * 20);
	if (emptyBuffer == nullptr) {
		console_print(xorstr_("Unable to allocate memory\n"));
		return { };
	}
	memset(emptyBuffer, 0, 1024 * 1024 * 20);

	// CLEAR PE HEAD
	if (!WriteProcessMemory(hProc, pTargetBase, emptyBuffer, 0x1000, nullptr)) {
		console_print(xorstr_("WARNING!: Can't clear HEADER\n"));
	}
	// ..

	// ADJUST PROTECTIONS
	pSectionHeader = IMAGE_FIRST_SECTION(pOldNtHeader);
	for (UINT i = 0; i != pOldFileHeader->NumberOfSections; ++i, ++pSectionHeader) {
		if (pSectionHeader->Misc.VirtualSize) {
			DWORD old = 0;
			DWORD newP = PAGE_READONLY;

			if ((pSectionHeader->Characteristics & IMAGE_SCN_MEM_WRITE) > 0) {
				newP = PAGE_READWRITE;
			}
			else if ((pSectionHeader->Characteristics & IMAGE_SCN_MEM_EXECUTE) > 0) {
				newP = PAGE_EXECUTE_READ;
			}
			if (VirtualProtectEx(hProc, pTargetBase + pSectionHeader->VirtualAddress, pSectionHeader->Misc.VirtualSize, newP, &old)) {
				console_print(xorstr_("section %s set as %lX\n"), (char*)pSectionHeader->Name, newP);
			}
			else {
				console_print(xorstr_("FAIL: section %s not set as %lX\n"), (char*)pSectionHeader->Name, newP);
			}
		}
	}
	DWORD old = 0;
	VirtualProtectEx(hProc, pTargetBase, IMAGE_FIRST_SECTION(pOldNtHeader)->VirtualAddress, PAGE_READONLY, &old);
	// ..

	*pBase = (uintptr_t) pTargetBase;
	return script;
}

#define RELOC_FLAG32(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_HIGHLOW)
#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef _WIN64
#define RELOC_FLAG RELOC_FLAG64
#else
#define RELOC_FLAG RELOC_FLAG32
#endif

#pragma runtime_checks( "", off )
#pragma optimize( "", off )
void __stdcall Shellcode(MANUAL_MAPPING_DATA* pData, Script& script_data) {
	if (!pData) {
		pData->hMod = (HINSTANCE)0x404040;
		return;
	}

	BYTE* pBase = pData->pbase;
	auto* pOpt = &reinterpret_cast<IMAGE_NT_HEADERS*>(pBase + reinterpret_cast<IMAGE_DOS_HEADER*>((uintptr_t)pBase)->e_lfanew)->OptionalHeader;

	auto _DllMain = reinterpret_cast<f_DLL_ENTRY_POINT>(pBase + pOpt->AddressOfEntryPoint);

	BYTE* LocationDelta = pBase - pOpt->ImageBase;
	if (LocationDelta) {
		if (pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) {
			auto* pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
			const auto* pRelocEnd = reinterpret_cast<IMAGE_BASE_RELOCATION*>(reinterpret_cast<uintptr_t>(pRelocData) + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);
			while (pRelocData < pRelocEnd && pRelocData->SizeOfBlock) {
				UINT AmountOfEntries = (pRelocData->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
				WORD* pRelativeInfo = reinterpret_cast<WORD*>(pRelocData + 1);

				for (UINT i = 0; i != AmountOfEntries; ++i, ++pRelativeInfo) {
					if (RELOC_FLAG(*pRelativeInfo)) {
						UINT_PTR* pPatch = reinterpret_cast<UINT_PTR*>(pBase + pRelocData->VirtualAddress + ((*pRelativeInfo) & 0xFFF));
						*pPatch += reinterpret_cast<UINT_PTR>(LocationDelta);
					}
				}
				pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(reinterpret_cast<BYTE*>(pRelocData) + pRelocData->SizeOfBlock);
			}
		}
	}

	if (pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {
		auto* pImportDescr = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
		while (pImportDescr->Name) {
			char* szMod = reinterpret_cast<char*>(pBase + pImportDescr->Name);
			HINSTANCE hDll = LoadLibraryA(szMod);

			ULONG_PTR* pThunkRef = reinterpret_cast<ULONG_PTR*>(pBase + pImportDescr->OriginalFirstThunk);
			ULONG_PTR* pFuncRef = reinterpret_cast<ULONG_PTR*>(pBase + pImportDescr->FirstThunk);

			if (!pThunkRef)
				pThunkRef = pFuncRef;

			for (; *pThunkRef; ++pThunkRef, ++pFuncRef) {
				if (IMAGE_SNAP_BY_ORDINAL(*pThunkRef)) {
					*pFuncRef = (ULONG_PTR)GetProcAddress(hDll, reinterpret_cast<char*>(*pThunkRef & 0xFFFF));
				}
				else {
					auto* pImport = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(pBase + (*pThunkRef));
					*pFuncRef = (ULONG_PTR)GetProcAddress(hDll, pImport->Name);
				}
			}
			++pImportDescr;
		}
	}

	if (pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size) {
		auto* pTLS = reinterpret_cast<IMAGE_TLS_DIRECTORY*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		auto* pCallback = reinterpret_cast<PIMAGE_TLS_CALLBACK*>(pTLS->AddressOfCallBacks);
		for (; pCallback && *pCallback; ++pCallback)
			(*pCallback)(pBase, DLL_PROCESS_ATTACH, nullptr);
	}

	if (pData->SEHSupport) {
		auto excep = pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
		if (excep.Size) {
			if (!RtlAddFunctionTable(
				reinterpret_cast<IMAGE_RUNTIME_FUNCTION_ENTRY*>(pBase + excep.VirtualAddress),
				excep.Size / sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY), (DWORD64)pBase)) {
			}
		}
	}

	_DllMain(pBase, DLL_PROCESS_ATTACH, nullptr);

	const auto export_directory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	const auto export_functions = reinterpret_cast<std::uint32_t*>(pBase + export_directory->AddressOfFunctions);
	const auto export_names = reinterpret_cast<std::uint32_t*>(pBase + export_directory->AddressOfNames);
	const auto export_ordinals = reinterpret_cast<std::uint16_t*>(pBase + export_directory->AddressOfNameOrdinals);

	for (auto i = 0u; i < export_directory->NumberOfNames; i++)
	{
		const auto export_name = reinterpret_cast<const char*>(pBase + export_names[i]);
		uintptr_t data = (uintptr_t) pBase + export_functions[export_ordinals[i]];

		if (!std::strcmp(export_name, xorstr_("script_name")))
			script_data.name = *(std::string*)data;
		if (!std::strcmp(export_name, xorstr_("script_type")))
			script_data.type = *(ScriptType*) data;
		if (!std::strcmp(export_name, xorstr_("script_champions")))
			script_data.supported_champions = *(std::vector<uint32_t>*)data;
		if (!std::strcmp(export_name, xorstr_("on_load_sdk")))
			script_data.sdk_load = (on_sdk_load)data;
		if (!std::strcmp(export_name, xorstr_("on_unload_sdk")))
			script_data.sdk_unload = (on_sdk_unload)data;
	}

	pData->hMod = reinterpret_cast<HINSTANCE>(pBase);
	script_data.initialized = true;
}
