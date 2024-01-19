#pragma once

class GameObject;

class EffectCreateDataClient
{
public:
    uint32_t get_effect_hash();
    GameObject* get_effect_emitter();
};
