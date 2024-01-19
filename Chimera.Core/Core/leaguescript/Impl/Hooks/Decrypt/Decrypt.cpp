#include "../pch.h"
#include "Decrypt.h"

static inline std::uint8_t* find_signature(const wchar_t* szModule, const char* szSignature) noexcept
{
	const auto module{ ::GetModuleHandle(szModule) };

	using bytes_t = std::vector<std::int32_t>;

	static const auto pattern_to_byte = [](const char* pattern) noexcept -> bytes_t
		{
			bytes_t bytes{};
			const auto start{ const_cast<char*>(pattern) };
			const auto end{ const_cast<char*>(pattern) + strlen(pattern) };

			for (auto current{ start }; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else
				{
					bytes.push_back(strtoul(current, &current, 16));
				}
			}

			return bytes;
		};

	const auto dosHeader{ reinterpret_cast<PIMAGE_DOS_HEADER>(module) };
	const auto ntHeaders{ reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dosHeader->e_lfanew) };
	const auto textSection{ IMAGE_FIRST_SECTION(ntHeaders) };

	const auto sizeOfImage{ textSection->SizeOfRawData };
	const auto patternBytes{ pattern_to_byte(szSignature) };
	const auto scanBytes{ reinterpret_cast<std::uint8_t*>(module) + textSection->VirtualAddress };

	const auto s{ patternBytes.size() };
	const auto d{ patternBytes.data() };

	MEMORY_BASIC_INFORMATION mbi{ 0 };
	std::uint8_t* next_check_address{ 0 };

	bool second{ false };

	for (auto i{ 0ul }; i < sizeOfImage - s; ++i)
	{
		bool found{ true };
		for (auto j{ 0ul }; j < s; ++j)
		{
			const auto current_address{ scanBytes + i + j };
			if (current_address >= next_check_address)
			{
				if (!::VirtualQuery(reinterpret_cast<void*>(current_address), &mbi, sizeof(mbi)))
					break;

				if (mbi.Protect == PAGE_NOACCESS) {

					i += ((std::uintptr_t(mbi.BaseAddress) + mbi.RegionSize) - (std::uintptr_t(scanBytes) + i));
					i--;
					found = false;
					break;
				}
				else {
					next_check_address = reinterpret_cast<std::uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
				}
			}

			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found && second)
			return &scanBytes[i];

		if (!second)
			second = true;
	}

	return nullptr;
}

inline void trigger_veh(uint64_t address)
{
	static auto func_addy = find_signature(nullptr, skCrypt("48 8B 41 08 48 85 C0 74 04 48 8B 00"));

	static auto deref_pointer_in_game_space_fn =
		(uint64_t(__fastcall*)(uint64_t))(func_addy);
	deref_pointer_in_game_space_fn(address - 0x8);
}

void LeagueDecrypt::decrypt(uintptr_t address) {
	__try {
		trigger_veh(address);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {}
}