#pragma once

#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"
#include "../Framework/Navigation/NavigationPath/NavigationPath.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

class NavigationMesh {};

class PathControllerCommon final
{
public:
	NavigationMesh* get_navigation_mesh() const;
	NavigationPath* get_navigation_path() const;

	bool is_dashing() const;
	float dash_speed() const;
	bool is_moving() const;

	const Vec3& get_server_pos() const;

	std::vector<Vec3> build_navigation_path(const Vec3& from, const Vec3& to, bool smooth = true);

	EXPORT_FUNC(bool, is_moving, (PathControllerCommon* obj), ());
	EXPORT_FUNC(bool, is_dashing, (PathControllerCommon* obj), ());
	EXPORT_FUNC(float, dash_speed, (PathControllerCommon* obj), ());
	EXPORT_FUNC(const Vec3&, get_server_pos, (PathControllerCommon* obj), ());
	EXPORT_FUNC(std::vector<Vec3>, build_navigation_path, (PathControllerCommon* obj, const Vec3& from, const Vec3& to, bool smooth), (from, to, smooth));

	// ========== NAVIGATION PATH ==========
	std::vector<Vec3> get_nav_waypoints() const;
	std::vector<Vec2> get_nav_waypoints_2d() const;
	int get_curr_segment() const;
	const Vec3& get_nav_start() const;
	const Vec3& get_nav_end() const;
	Vec3* get_nav_array() const;
	int get_nb_waypoints() const;
	float get_path_length() const;

	EXPORT_FUNC(std::vector<Vec3>, get_nav_waypoints, (PathControllerCommon* obj), ());
	EXPORT_FUNC(std::vector<Vec2>, get_nav_waypoints_2d, (PathControllerCommon* obj), ());
	EXPORT_FUNC(int, get_curr_segment, (PathControllerCommon* obj), ());
	EXPORT_FUNC(const Vec3&, get_nav_start, (PathControllerCommon* obj), ());
	EXPORT_FUNC(const Vec3&, get_nav_end, (PathControllerCommon* obj), ());
	EXPORT_FUNC(int, get_nb_waypoints, (PathControllerCommon* obj), ());
	EXPORT_FUNC(float, get_path_length, (PathControllerCommon* obj), ());
};

#ifdef EXPORT_FUNC
#undef EXPORT_FUNC
#endif