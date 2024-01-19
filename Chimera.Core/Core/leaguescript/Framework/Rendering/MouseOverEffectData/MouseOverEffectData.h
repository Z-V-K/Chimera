#pragma once

#include "../Impl/Common/Common.h"

class MouseOverEffectData final
{
public:
	D3DCOLOR* get_color_array();
	int get_size();
	int get_blur();
};