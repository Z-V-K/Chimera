#pragma once
#include "DamageItem.h"

struct Stormrazor : DamageItem
{
    Stormrazor() : DamageItem(ItemId::Stormrazor, DamageType::Magical) { }

    DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
    {
        return { 90.0 + 0.25 * (double)source->get_total_ad(), 0.0, 0.0 };
    }

    bool is_active(GameObject* source, GameObject* target) override
    {
        return source->get_buff_count(0xc4266ca1) == 100;
    }
};