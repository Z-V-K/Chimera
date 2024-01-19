#pragma once
#include "../../../Impl/Vector/Vector.h"

class r3dTexture final
{
private:
	uintptr_t get_texture_data();
public:
	std::string_view get_texture_name();
	PVOID get_dx_texture();
	Vec4 get_uv();
};
