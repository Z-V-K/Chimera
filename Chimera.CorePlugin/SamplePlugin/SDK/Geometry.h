#pragma once

#include "SDK.h"
#include "clipper2/clipper.h"

namespace Geometry
{
	class Polygon
	{
	public:
		std::vector<Vec3> points { };

		void add(const Vec3& point);
		bool is_inside(const Vec3& point) const;
		bool is_outside(const Vec3& point) const;
		Clipper2Lib::PathD to_clipper_path() const;
		void draw(const Color col, int thickness, bool draw_points = true) const;
	};

	class Arc
	{
	public:
		Vec3 start;
		Vec3 end;
		int hit_box;
		float distance;

		Arc(const Vec3& start, const Vec3& end, int hitbox) :
			start(start), end(end), hit_box(hitbox), distance(start.distance(end))
		{ }

		std::vector<Vec3> circle_circle_intersection(const Vec3& center1, const Vec3& center2, float radius1, float radius2) const;
		Polygon to_polygon(int offset = 0) const;
	};

	class Circle
	{
	public:
		Vec3 center;
		float radius;

		Circle(const Vec3& center, float radius) :
			center(center), radius(radius)
		{ }

		Polygon to_polygon(int offset = 0, float override_width = -1) const;
	};

	class Rectangle
	{
	public:
		Vec3 rStart;
		Vec3 rEnd;
		float width;
		Vec3 direction;
		Vec3 perpendicular;

		Rectangle(const Vec3& start, const Vec3& end, float width) :
			rStart(start), rEnd(end), width(width), direction((end - start).normalized()), perpendicular(direction.perpendicular())
		{ }

		Polygon to_polygon(int offset = 0, float overrideWidth = -1) const;
	};

	class Ring
	{
	public:
		Vec3 center;
		float radius;
		float outerRadius;

		Ring(const Vec3& center, float radius, float outer_radius) :
		 center(center), radius(radius), outerRadius(outer_radius)
		{ }

		Polygon to_polygon(int offset = 0) const;
	};

	class Sector
	{
	public:
		float angle;
		Vec3 center;
		Vec3 direction;
		float radius;

		Sector(const Vec3& center, const Vec3& direction, float angle, float radius) :
			angle(angle), center(center), direction(direction), radius(radius)
		{ }

		Polygon to_polygon(int offset = 0) const;
	};

	struct MecCircle
	{
		MecCircle(const Vec2& center, float radius) :
			center(center),
			radius(radius)
		{ }

		Vec2 center;
		float radius;
	};

	struct Rectangle_f
	{
		Rectangle_f(float x, float y, float w, float h) :
			x(x),
			y(y),
			width(w),
			height(h)
		{ }

		float x;
		float y;
		float width;
		float height;
	};

	class Mec
	{
	public:
		static MecCircle get_mec(const std::vector<Vec2>& points);
		static void find_circle(const Vec2& a, const Vec2& b, const Vec2& c, Vec2& center, float& radius2);
		static void find_minimal_bounding_circle(const std::vector<Vec2>& points, Vec2& center, float& radius);
		static void get_min_max_corners(const std::vector<Vec2>& points, Vec2& ul, Vec2& ur, Vec2& ll, Vec2& lr);
		static Rectangle_f get_min_max_box(const std::vector<Vec2>& points);
		static std::vector<Vec2> hull_cull(const std::vector<Vec2>& points);
		static float angle_value(float x1, float y1, float x2, float y2);
		static std::vector<Vec2> make_convex_hull(std::vector<Vec2> points);
	};

	Clipper2Lib::PathsD		clip_polygons(std::vector<Polygon>& polygons);
	Polygon					to_polygon(const Clipper2Lib::PathD& v);
	std::vector<Polygon>	to_polygons(const Clipper2Lib::PathsD& v);
}