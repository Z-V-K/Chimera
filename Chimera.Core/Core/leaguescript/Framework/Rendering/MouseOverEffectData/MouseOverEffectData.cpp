#include "../pch.h"
#include "MouseOverEffectData.h"

D3DCOLOR* MouseOverEffectData::get_color_array()
{
	return RVA_CAST_THIS_REF(D3DCOLOR*, Structures::MouseOverEffectData::Color);
}
int MouseOverEffectData::get_size()
{
	return RVA_CAST_THIS(int, Structures::MouseOverEffectData::Size);
}
int MouseOverEffectData::get_blur()
{
	return RVA_CAST_THIS(int, Structures::MouseOverEffectData::Blur);
}