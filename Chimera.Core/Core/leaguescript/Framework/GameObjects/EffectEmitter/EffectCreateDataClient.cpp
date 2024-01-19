#include "EffectCreateDataClient.h"

#include "../../../Impl/Common/Common.h"

uint32_t EffectCreateDataClient::get_effect_hash()
{
    return RVA_CAST_THIS(uint32_t, Structures::EffectCreateDataClient::EffectHash);
}

GameObject* EffectCreateDataClient::get_effect_emitter()
{
    return RVA_CAST_THIS(GameObject*, Structures::EffectCreateDataClient::Emitter);
}
