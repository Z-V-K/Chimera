#pragma once

template<typename T>
struct ManagerTemplate
{
	uintptr_t vtable;
	T** entities;
	int size;
	int max_size;
};
