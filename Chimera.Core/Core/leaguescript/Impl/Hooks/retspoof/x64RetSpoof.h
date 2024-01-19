#pragma once

#include "../Impl/Base/base.h"

namespace x64RetSpoof
{
	extern "C" void* _spoofer_stub();

	inline uintptr_t spoof_addr = 0x0;

	static inline void initialize()
	{
		spoof_addr = (uintptr_t) base::find_pattern(nullptr, skCrypt("FF 23"));
	}

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
		static auto do_call(
			const void* shell,
			void* shell_param,
			First first,
			Second second,
			Third third,
			Fourth fourth,
			Pack... pack
		) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
				);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
		static auto do_call(
			const void* shell,
			void* shell_param,
			First first = First{},
			Second second = Second{},
			Third third = Third{},
			Fourth fourth = Fourth{}
		) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};

	template <typename Ret, typename... Args>
	static inline auto spoof_call(
		Ret(*fn)(Args...),
		Args... args
	) -> Ret
	{
		struct shell_params
		{
			const void* trampoline = nullptr;
			void* function = nullptr;
			void* rbx = nullptr;
		};

		shell_params p{ (void*) spoof_addr, reinterpret_cast<void*>(fn) };
		using mapper = argument_remapper<sizeof...(Args), void>;

		return mapper::template do_call<Ret, Args...>((const void*)&_spoofer_stub, &p, args...);
	}
}