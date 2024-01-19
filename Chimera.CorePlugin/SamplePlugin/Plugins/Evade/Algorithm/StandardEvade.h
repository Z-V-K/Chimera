#pragma once

class StandardEvade
{
public:
    static std::vector<Vec3> run(const Vec3& start_pos, const Vec3& end_pos, float movement_speed, float delay);
};
