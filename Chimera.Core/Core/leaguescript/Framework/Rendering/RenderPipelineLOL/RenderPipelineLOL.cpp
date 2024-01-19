#include "../pch.h"
#include "RenderPipelineLOL.h"

MouseOverEffectData* RenderPipelineLOL::get_default_mouse_over_effect_data()
{
	return RVA_CAST_THIS(MouseOverEffectData*, Structures::RenderPipelineLOL::DefaultMouseOverEffectData);
}