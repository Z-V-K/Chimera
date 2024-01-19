#pragma once
#include "DamageItem.h"

struct TitanicHydra : DamageItem
{
    TitanicHydra() : DamageItem(ItemId::Titanic_Hydra, DamageType::Physical) { }

    DamageOutput get_damage(GameObject* source, GameObject* target, bool is_auto) override
    {
        return { 0.0, (source->is_melee() ? 4.0 : 3.0) + (source->is_melee() ? 0.015 : 0.01125) * (double)source->get_max_health(), 0.0 };
    }
};