#pragma once
#include "EvadeGrid.h"

class ThetaStar
{
public:
    static std::vector<EvadeGrid::Node*> run(EvadeGrid& grid, const Vec3& start_pos, const Vec3& end_pos, float movement_speed, float delay);
};
