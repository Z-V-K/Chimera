#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"

class GameObject;

class NavigationPath final
{
	// memory allocation
	char pad[0x80];
private:
public:
	std::vector<Vec3> get_nav_waypoints();
	std::vector<Vec2> get_nav_waypoints_2d();
	int get_curr_segment();
	const Vec3& get_nav_start();
	const Vec3& get_nav_end();
	Vec3* get_nav_array();
	int get_nb_waypoints();
};
