#pragma once

#include "../Impl/Vector/Vector.h"

class EffectEmitterAttachment;
class EffectEmitterData;
class GameObject;

class EffectEmitter
{
public:
    EffectEmitterData* get_data();
    EffectEmitterAttachment* get_attachment();
    EffectEmitterAttachment* get_target_attachment();
};
