#pragma once

#include "EffectEmitterAttachment.h"
#include "../Impl/Vector/Vector.h"

class GameObject;

class EffectEmitterData
{
public:
    Vec3 get_forward();
    Vec3 get_up();
    Vec3 get_right();
};
