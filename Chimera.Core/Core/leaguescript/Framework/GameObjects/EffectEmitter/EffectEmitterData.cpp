#include "EffectEmitterData.h"

Vec3 EffectEmitterData::get_forward()
{
    return RVA_CAST_THIS(Vec3, Structures::EffectEmitterData::OrientationForward);
}

Vec3 EffectEmitterData::get_right()
{
    return RVA_CAST_THIS(Vec3, Structures::EffectEmitterData::OrientationRight);
}

Vec3 EffectEmitterData::get_up()
{
    return RVA_CAST_THIS(Vec3, Structures::EffectEmitterData::OrientationUp);
}