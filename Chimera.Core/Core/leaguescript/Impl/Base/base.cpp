#include "../pch.h"

#include "base.h"

namespace base
{
#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

    uint8_t* find_pattern(const char* szModule, const char* signature)
    {
		auto module = GetModuleHandleA(szModule);
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)module + dosHeader->e_lfanew);
		auto textSection = IMAGE_FIRST_SECTION(ntHeaders);

		auto sizeOfImage = textSection->SizeOfRawData;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<uint8_t*>(module) + textSection->VirtualAddress;

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		auto mbi = MEMORY_BASIC_INFORMATION{ 0 };
		uint8_t* next_check_address = 0;

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				auto current_address = scanBytes + i + j;
				if (current_address >= next_check_address) {
					if (!VirtualQuery(reinterpret_cast<void*>(current_address), &mbi, sizeof(mbi)))
						break;

					if (mbi.Protect == PAGE_NOACCESS) {
						i += ((std::uintptr_t(mbi.BaseAddress) + mbi.RegionSize) - (std::uintptr_t(scanBytes) + i));
						i--;
						found = false;
						break;
					}
					else {
						next_check_address = reinterpret_cast<uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
					}
				}

				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scanBytes[i];
			}
		}
		return nullptr;
    }
}