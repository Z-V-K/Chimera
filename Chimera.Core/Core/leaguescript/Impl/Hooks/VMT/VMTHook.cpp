#include "../pch.h"
#include "VMTHook.h"

void* custom_memcpy(void* dest, const void* src, unsigned __int64 count)
{
	char* char_dest = (char*)dest;
	char* char_src = (char*)src;
	if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
	{
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest++;
			char_src++;
			count--;
		}
	}
	else
	{
		char_dest = (char*)dest + count - 1;
		char_src = (char*)src + count - 1;
		while (count > 0)
		{
			*char_dest = *char_src;
			char_dest--;
			char_src--;
			count--;
		}
	}
	return dest;
}

bool VMTHook::initialize(void* original)
{
	if (original)
	{
		originalVMT = reinterpret_cast<uintptr_t**>(original);
		copiedVMT = *originalVMT;

		while (reinterpret_cast<void*>(copiedVMT[iMethods]))
		{
			iMethods++;
		}

		if (iMethods > 0)
		{
			ourVMT = std::make_unique<std::uintptr_t[]>(iMethods);
			custom_memcpy(ourVMT.get(), copiedVMT, iMethods * sizeof(std::uintptr_t));
		}
	}
	return ourVMT != nullptr;
}

uintptr_t VMTHook::hook(void* original, const size_t& index, const uintptr_t& function)
{
	if (!initialize(original))
		return false;

	return hook_index(index, function);
}

uintptr_t VMTHook::hook_index(const size_t& index, const uintptr_t& function)
{
	if (ourVMT && index < iMethods)
	{
		ourVMT[index] = function;

		*originalVMT = ourVMT.get();
		bEnabled = true;

		return copiedVMT[index];
	}
	return 0;
}

bool VMTHook::unhook()
{
	if (bEnabled)
	{
		*originalVMT = copiedVMT;
		bEnabled = false;
		return true;
	}

	return false;
}