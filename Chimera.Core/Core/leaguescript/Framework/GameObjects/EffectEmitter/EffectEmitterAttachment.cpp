#include "EffectEmitterAttachment.h"

#include "../../../Impl/Common/Common.h"

GameObject* EffectEmitterAttachment::get_object()
{
    const uintptr_t data = RVA_CAST_THIS(uintptr_t, Structures::EffectEmitterAttachment::Data);
    return data ? *(GameObject**) (data + (uintptr_t) Structures::EffectEmitterAttachment::Object) : nullptr;
}