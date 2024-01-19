#include "../pch.h"
#include "r3dTexture.h"
#include "../Addresses/Structures.h"

uintptr_t r3dTexture::get_texture_data()
{
	return RVA_CAST_THIS(uintptr_t, Structures::r3dTexture::TextureData);
}

PVOID r3dTexture::get_dx_texture()
{
	const uintptr_t textureData = get_texture_data();

	return *reinterpret_cast<void**>((uintptr_t)textureData + (uintptr_t)Structures::r3dTexture::DXTexture);
}

std::string_view r3dTexture::get_texture_name()
{
	return RVA_CAST_THIS(std::string, Structures::r3dTexture::TextureName);
}

Vec4 r3dTexture::get_uv()
{
	return RVA_CAST_THIS(Vec4, Structures::r3dTexture::UV);
}
