#include "EffectEmitter.h"

#include "EffectEmitterAttachment.h"
#include "EffectEmitterData.h"
#include "../Impl/Common/Common.h"

EffectEmitterData* EffectEmitter::get_data()
{
    return RVA_CAST_THIS(EffectEmitterData*, Structures::EffectEmitter::Data);
}

EffectEmitterAttachment* EffectEmitter::get_attachment()
{
    return RVA_CAST_THIS(EffectEmitterAttachment*, Structures::EffectEmitter::Attachment);
}

EffectEmitterAttachment* EffectEmitter::get_target_attachment()
{
    return RVA_CAST_THIS(EffectEmitterAttachment*, Structures::EffectEmitter::TargetAttachment);
}