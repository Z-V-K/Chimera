#pragma once
#include "DamageItem.h"

struct TearOfTheGoddess : DamageItem
{
    TearOfTheGoddess() : DamageItem(ItemId::Tear_of_the_Goddess, DamageType::Physical) { }

    DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
    {
        return { 0.0, target->is_minion() ? 5.0 : 0.0, 0.0 };
    }

    bool is_active(GameObject* source, GameObject* target) override
    {
        return source->get_item(item_id) != nullptr && target->is_minion();
    }
};