#pragma once
#include "../Impl/Vector/Vector.h"

struct SetPathDashData
{
    float dash_speed;
    char pad[0x4C];
    Vec3 start_pos;
    Vec3 end_pos;
};
