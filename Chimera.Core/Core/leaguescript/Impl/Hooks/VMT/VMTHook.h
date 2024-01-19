#pragma once

class VMTHook
{
private:
	uintptr_t** originalVMT = nullptr;
	uintptr_t* copiedVMT = nullptr;
	std::unique_ptr<std::uintptr_t[]> ourVMT = nullptr;
	size_t iMethods = 0;
	bool bEnabled = false;

public:

	VMTHook(void* original = nullptr)
	{
		if (original)
			initialize(original);
	}
	//   VMTHook(void* original, size_t index, uintptr_t function)
	   //{
	   //	Hook(original, index, function);
	   //}

	~VMTHook()
	{
		if (bEnabled)
			unhook();

		originalVMT = nullptr;
		copiedVMT = nullptr;
		ourVMT.reset();

		iMethods = 0;
	}

	bool initialize(void* original);

	uintptr_t hook(void* original, const size_t& index, const uintptr_t& function);

	bool unhook();

	uintptr_t hook_index(const size_t& index, const uintptr_t& function);
};