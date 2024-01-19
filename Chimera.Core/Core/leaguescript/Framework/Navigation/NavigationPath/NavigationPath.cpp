#include "../pch.h"
#include "../Framework/Navigation/NavigationPath/NavigationPath.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"

std::vector<Vec2> NavigationPath::get_nav_waypoints_2d()
{
	std::vector<Vec2> path{};

	if (reinterpret_cast<uintptr_t>(this) <= 0x1000)
		return path;

	if (!get_nav_array())
		return path;

	const int size{ get_nb_waypoints() };

	if (size > 100 || size <= 0)
		return path;

	for (int i{ this->get_curr_segment() }; i < size; i++) {
		Vec3 nav{ get_nav_array()[i] };
		path.emplace_back(nav.to_2d());
	}

	return path;
}

std::vector<Vec3> NavigationPath::get_nav_waypoints()
{
	std::vector<Vec3> path{};

	if (reinterpret_cast<uintptr_t>(this) <= 0x1000)
		return path;

	if (!get_nav_array())
		return path;

	const int size{ get_nb_waypoints() };

	if (size > 100 || size <= 0)
		return path;

	for (int i{ this->get_curr_segment() }; i < size; i++) {
		Vec3 nav{ get_nav_array()[i] };
		path.emplace_back(nav);
	}
	
	return path;
}

int NavigationPath::get_curr_segment()
{
	return RVA_CAST_THIS(int, Structures::NavigationPath::CurrSegment);
}

const Vec3& NavigationPath::get_nav_start()
{
	return RVA_CAST_THIS(Vec3, Structures::NavigationPath::NavStart);
}

const Vec3& NavigationPath::get_nav_end()
{
	return RVA_CAST_THIS(Vec3, Structures::NavigationPath::NavEnd);
}

Vec3* NavigationPath::get_nav_array()
{
	return RVA_CAST_THIS(Vec3*, Structures::NavigationPath::NavArray);
}

int NavigationPath::get_nb_waypoints()
{
	return RVA_CAST_THIS(int, Structures::NavigationPath::NbWaypoints);
}