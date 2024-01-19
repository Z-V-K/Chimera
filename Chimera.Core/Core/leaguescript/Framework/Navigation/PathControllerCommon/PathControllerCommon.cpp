#include "../pch.h"
#include "PathControllerCommon.h"
#include "../Impl/Base/base.h"

#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

NavigationMesh* PathControllerCommon::get_navigation_mesh() const
{
	return RVA_CAST_THIS(NavigationMesh*, Structures::PathControllerCommon::NavigationMesh);
}

NavigationPath* PathControllerCommon::get_navigation_path() const
{
	return RVA_CAST_THIS_REF(NavigationPath*, Structures::PathControllerCommon::NavigationPath);
}

bool PathControllerCommon::is_dashing() const
{
	return RVA_CAST_THIS(bool, Structures::PathControllerCommon::IsDashing);
}

float PathControllerCommon::dash_speed() const
{
	return RVA_CAST_THIS(float, Structures::PathControllerCommon::DashSpeed);
}

bool PathControllerCommon::is_moving() const
{
	return get_path_length() > 15.0f;
}

const Vec3& PathControllerCommon::get_server_pos() const
{
	return RVA_CAST_THIS(Vec3, Structures::PathControllerCommon::ServerPos);
}

std::vector<Vec3> PathControllerCommon::get_nav_waypoints() const
{
	std::vector<Vec3> waypoints = get_navigation_path()->get_nav_waypoints();
	waypoints.insert(waypoints.begin(), get_server_pos());
	return waypoints;
}

std::vector<Vec2> PathControllerCommon::get_nav_waypoints_2d() const
{
	std::vector<Vec2> waypoints = get_navigation_path()->get_nav_waypoints_2d();
	waypoints.insert(waypoints.begin(), get_server_pos().to_2d());
	return waypoints;
}

int PathControllerCommon::get_curr_segment() const
{
	return get_navigation_path()->get_curr_segment();
}

const Vec3& PathControllerCommon::get_nav_start() const
{
	return get_navigation_path()->get_nav_start();
}

const Vec3& PathControllerCommon::get_nav_end() const
{
	return get_navigation_path()->get_nav_end();
}

Vec3* PathControllerCommon::get_nav_array() const
{
	return get_navigation_path()->get_nav_array();
}

int PathControllerCommon::get_nb_waypoints() const
{
	return get_navigation_path()->get_nb_waypoints();
}

float PathControllerCommon::get_path_length() const
{
	float length = 0;
	const auto waypoints = get_nav_waypoints();

	for (size_t i = 1; i < waypoints.size(); ++i)
		length += waypoints[i - 1].distance(waypoints[i]);

	return length;
}

std::vector<Vec3> PathControllerCommon::build_navigation_path(const Vec3& from, const Vec3& to, bool smooth)
{
	bool unk1, unk3;
	float unk2[12];
	int maxNodes = 10000;

	NavigationPath navPath{};

	typedef char (__fastcall* fnBuildPath)(uintptr_t, NavigationPath*, const Vec3*, const Vec3*, uintptr_t, int, bool*, float(*)[12], bool*, int, int);
	static fnBuildPath fn = (fnBuildPath)MAKE_RVA(Addresses::PathControllerCommon::BuildNavigationPath);
	x64RetSpoof::spoof_call(fn, (uintptr_t)get_navigation_mesh(), &navPath, &from, &to, (uintptr_t) this, 0, &unk1, &unk2, &unk3, maxNodes, 0);

	/*if (smooth)
	{
		typedef int64_t(__fastcall* fnSmoothPath)(uintptr_t, NavigationPath*);
		static fnSmoothPath fn = (fnSmoothPath)MAKE_RVA(Addresses::PathControllerCommon::SmoothPath);
		x64RetSpoof::spoof_call(fn, (uintptr_t) this, &navPath);
	}*/

	return navPath.get_nav_waypoints();
}