#include "../pch.h"
#include "Geometry.h"

#define CircleLineSegmentN 40

namespace Geometry
{
	void Polygon::add(const Vec3& point)
	{
		points.push_back(point);
	}

	bool Polygon::is_inside(const Vec3& point) const
	{
		auto path = to_clipper_path();
		return Clipper2Lib::PointInPolygon(Clipper2Lib::Point<double>(point.x, point.z), path) != Clipper2Lib::PointInPolygonResult::IsOutside;
	}

	bool Polygon::is_outside(const Vec3& point) const
	{
		return !is_inside(point);
	}

	Clipper2Lib::PathD Polygon::to_clipper_path() const
	{
		std::vector<int> points_2d;

		for (const auto& point : points)
		{
			points_2d.push_back((int) point.x);
			points_2d.push_back((int) point.z);
		}

		return Clipper2Lib::MakePathD(points_2d);
	}

	void Polygon::draw(const Color col, int thickness, bool draw_points) const
	{
		for (int i = 0; i < points.size(); i++)
		{
			auto nextIndex = (points.size() - 1 == i) ? 0 : (i + 1);
			draw_manager->line(points[i], points[nextIndex], col, thickness);

			if (draw_points)
				draw_manager->circle(points[i], 5, Color(180, 180, 180, 255), 1.f, true);
		}
	}

	std::vector<Vec3> Arc::circle_circle_intersection(const Vec3& center1, const Vec3& center2, float radius1, float radius2) const
	{
		std::vector<Vec3> result;

		float d = center1.distance(center2);

		if (d > radius1 + radius2 || d <= abs(radius1 - radius2))
		{
			return result;
		}

		float a = (radius1 * radius1 - radius2 * radius2 + d * d) / (2 * d);
		float h = (float)sqrt(radius1 * radius1 - a * a);
		Vec3 direction = (center2 - center1).normalized();
		Vec3 pa = center1 + direction * a;
		Vec3 s1 = pa + direction.perpendicular() * h;
		Vec3 s2 = pa - direction.perpendicular() * h;

		result.push_back(s1);
		result.push_back(s2);
		return result;
	}

	Polygon Arc::to_polygon(int offset) const
	{
		offset += hit_box;
		Polygon result = Polygon();

		float innerRadius = -0.1562f * distance + 687.31f;
		float outerRadius = 0.35256f * distance + 133.0f;

		outerRadius = outerRadius / (float)cos(2 * M_PI / CircleLineSegmentN);

		auto innerCenters = circle_circle_intersection(start, end, innerRadius, innerRadius);
		auto outerCenters = circle_circle_intersection(start, end, outerRadius, outerRadius);

		Vec3 innerCenter = innerCenters[0];
		Vec3 outerCenter = outerCenters[0];

		Vec3 direction = (end - outerCenter).normalized();
		Vec3 end = (start - outerCenter).normalized();
		float maxAngle = (float)(direction.angle_between(end) * M_PI / 180.0f);

		float step = -maxAngle / CircleLineSegmentN;

		for (int i = 0; i < CircleLineSegmentN; i++)
		{
			float angle = step * i;
			Vec3 point = outerCenter + direction.rotated(angle) * (outerRadius + 15 + offset);
			result.add(point);
		}

		direction = (start - innerCenter).normalized();
		end = (end - innerCenter).normalized();
		maxAngle = (float)(direction.angle_between(end) * M_PI / 180.0f);
		step = maxAngle / CircleLineSegmentN;

		for (int i = 0; i < CircleLineSegmentN; i++)
		{
			float angle = step * i;
			Vec3 point = innerCenter + direction.rotated(angle) * fmax(0, innerRadius - offset - 20);
			result.add(point);
		}

		return result;
	}

	Polygon Circle::to_polygon(int offset, float override_width) const
	{
		Polygon result = Polygon();
		float outRadius = override_width > 0
			? override_width
			: (offset + radius) / (float)cos(2 * M_PI / CircleLineSegmentN);

		double step = 2 * M_PI / CircleLineSegmentN;
		double angle = radius;
		for (int i = 0; i <= CircleLineSegmentN; i++)
		{
			angle += step;
			Vec3 point = Vec3(center.x + outRadius * (float)cos(angle),
				this->center.y, center.z + outRadius * (float)sin(angle));
			result.add(point);
		}

		return result;
	}

	Polygon Rectangle::to_polygon(int offset, float overrideWidth) const
	{
		Polygon result = Polygon();

		result.add(rStart +
			perpendicular * (overrideWidth > 0 ? overrideWidth : width + offset) -
			direction * offset);
		result.add(rStart -
			perpendicular * (overrideWidth > 0 ? overrideWidth : width + offset) -
			direction * offset);
		result.add(rEnd -
			perpendicular * (overrideWidth > 0 ? overrideWidth : width + offset) +
			direction * offset);
		result.add(rEnd +
			perpendicular * (overrideWidth > 0 ? overrideWidth : width + offset) +
			direction * offset);

		return result;
	}

	Polygon Ring::to_polygon(int offset) const
	{
		Polygon result;

		float outRadius = (float)(offset + this->radius + this->outerRadius) / cosf(2 * M_PI / CircleLineSegmentN);
		float innerRadius = this->radius - this->outerRadius - offset;

		for (int i = 0; i <= CircleLineSegmentN; i++)
		{
			float angle = i * 2 * M_PI / CircleLineSegmentN;
			auto point = Vec3(
				this->center.x - outRadius * cosf(angle),
				this->center.y, this->center.z - outRadius * sinf(angle));

			result.add(point);
		}
		for (int i = 0; i <= CircleLineSegmentN; i++)
		{
			float angle = i * 2 * M_PI / CircleLineSegmentN;
			auto point = Vec3(
				this->center.x - innerRadius * cosf(angle),
				this->center.y, this->center.z - innerRadius * sinf(angle));

			result.add(point);
		}
		return result;
	}

	Polygon Sector::to_polygon(int offset) const
	{
		Polygon result = Polygon();
		float outRadius = (radius + offset) / (float)cos(2 * M_PI / CircleLineSegmentN);

		result.add(center);
		Vec3 side1 = direction.rotated(-angle * 0.5f);

		for (int i = 0; i <= CircleLineSegmentN; i++)
		{
			Vec3 cDirection = side1.rotated(i * angle / CircleLineSegmentN).normalized();
			result.add(Vec3(center.x + outRadius * cDirection.x,
				center.y, center.z + outRadius * cDirection.z));
		}

		return result;
	}

	MecCircle Mec::get_mec(const std::vector<Vec2>& points)
	{
		auto center = Vec2();
		float radius;

		auto convex_hull = make_convex_hull(points);
		find_minimal_bounding_circle(convex_hull, center, radius);
		return MecCircle(center, radius);
	}

	bool circle_encloses_points(
		const Vec2& center,
		float radius2,
		const std::vector<Vec2>& points,
		int skip1,
		int skip2,
		int skip3)
	{
		for (auto i = 0u; i < points.size(); i++)
		{
			if ((i != skip1) && (i != skip2) && (i != skip3))
			{
				Vec2 point = points[i];
				float dx = center.x - point.x;
				float dy = center.y - point.y;
				float test_radius2 = dx * dx + dy * dy;
				if (test_radius2 > radius2)
					return false;
			}
		}
		return true;
	}

	void Mec::find_circle(const Vec2& a, const Vec2& b, const Vec2& c, Vec2& center, float& radius2)
	{
		auto x1 = (b.x + a.x) / 2;
		auto y1 = (b.y + a.y) / 2;
		auto dy1 = b.x - a.x;
		auto dx1 = -(b.y - a.y);

		auto x2 = (c.x + b.x) / 2;
		auto y2 = (c.y + b.y) / 2;
		auto dy2 = c.x - b.x;
		auto dx2 = -(c.y - b.y);

		auto cx = (y1 * dx1 * dx2 + x2 * dx1 * dy2 - x1 * dy1 * dx2 - y2 * dx1 * dx2) / (dx1 * dy2 - dy1 * dx2);
		auto cy = (cx - x1) * dy1 / dx1 + y1;
		center = Vec2(cx, cy);

		auto dx = cx - a.x;
		auto dy = cy - a.y;
		radius2 = dx * dx + dy * dy;
	}

	void Mec::find_minimal_bounding_circle(const std::vector<Vec2>& points, Vec2& center, float& radius)
	{
		auto hull = make_convex_hull(points);

		auto best_center = points[0];
		auto best_radius2 = FLT_MAX;

		for (auto i = 0; i < (std::int32_t) hull.size() - 1; i++)
		{
			for (auto j = i + 1; j < (std::int32_t) hull.size(); j++)
			{
				auto test_center = Vec2((hull[i].x + hull[j].x) / 2.f, (hull[i].y + hull[j].y) / 2.f);
				auto dx = test_center.x - hull[i].x;
				auto dy = test_center.y - hull[i].y;
				auto test_radius2 = dx * dx + dy * dy;

				if (test_radius2 < best_radius2)
				{
					if (circle_encloses_points(test_center, test_radius2, points, i, j, -1))
					{
						best_center = test_center;
						best_radius2 = test_radius2;
					}
				}
			}
		}

		for (auto i = 0; i < (std::int32_t) hull.size() - 2; i++)
		{
			for (auto j = i + 1; j < (std::int32_t) hull.size() - 1; j++)
			{
				for (auto k = j + 1; k < (std::int32_t) hull.size(); k++)
				{
					Vec2 test_center;
					float test_radius2;
					find_circle(hull[i], hull[j], hull[k], test_center, test_radius2);

					if (test_radius2 < best_radius2)
					{
						if (circle_encloses_points(test_center, test_radius2, points, i, j, k))
						{
							best_center = test_center;
							best_radius2 = test_radius2;
						}
					}
				}
			}
		}

		center = best_center;
		if (best_radius2 == FLT_MAX)
		{
			radius = 0;
		}
		else
		{
			radius = sqrt(best_radius2);
		}
	}

	void Mec::get_min_max_corners(
		const std::vector<Vec2>& points,
		Vec2& ul,
		Vec2& ur,
		Vec2& ll,
		Vec2& lr )
	{
		ul = points[0];
		ur = ul;
		ll = ul;
		lr = ul;

		for (auto& pt : points)
		{
			if (-pt.x - pt.y > -ul.x - ul.y)
			{
				ul = pt;
			}
			if (pt.x - pt.y > ur.x - ur.y)
			{
				ur = pt;
			}
			if (-pt.x + pt.y > -ll.x + ll.y)
			{
				ll = pt;
			}
			if (pt.x + pt.y > lr.x + lr.y)
			{
				lr = pt;
			}
		}
	}

	Rectangle_f Mec::get_min_max_box(const std::vector<Vec2>& points)
	{
		Vec2 ul = { }, ur = ul, ll = ul, lr = ul;
		get_min_max_corners(points, ul, ur, ll, lr);

		auto xmin = ul.x;
		auto ymin = ul.y;

		auto xmax = ur.x;
		if (ymin < ur.y)
		{
			ymin = ur.y;
		}

		if (xmax > lr.x)
		{
			xmax = lr.x;
		}
		auto ymax = lr.y;

		if (xmin < ll.x)
		{
			xmin = ll.x;
		}
		if (ymax > ll.y)
		{
			ymax = ll.y;
		}

		auto result = Rectangle_f(xmin, ymin, xmax - xmin, ymax - ymin);
		return result;
	}

	std::vector<Vec2> Mec::hull_cull(const std::vector<Vec2>& points)
	{
		std::vector<Vec2> results;
		auto culling_box = get_min_max_box(points);

		for (auto& pt : points)
		{
			if (pt.x <= culling_box.x || pt.x >= culling_box.x + culling_box.width || pt.y <= culling_box.y
				|| pt.y >= culling_box.y + culling_box.height)
				results.push_back(pt);
		}


		return results;
	}

	float Mec::angle_value(float x1, float y1, float x2, float y2)
	{
		float t;

		auto dx = x2 - x1;
		auto ax = abs(dx);
		auto dy = y2 - y1;
		auto ay = abs(dy);
		if (ax + ay == 0)
		{
			t = 360.f / 9.f;
		}
		else
		{
			t = dy / (ax + ay);
		}
		if (dx < 0)
		{
			t = 2 - t;
		}
		else if (dy < 0)
		{
			t = 4 + t;
		}
		return t * 90;
	}

	std::vector<Vec2> Mec::make_convex_hull(std::vector<Vec2> points)
	{
		points = hull_cull(points);

		Vec2 best_pt = points[0];

		for (auto& pt : points)
		{
			if ((pt.y < best_pt.y) || ((pt.y == best_pt.y) && (pt.x < best_pt.x)))
				best_pt = pt;
		}

		std::vector<Vec2> hull;

		hull.push_back(best_pt);

		points.erase(std::remove(points.begin(), points.end(), best_pt), points.end());

		float sweep_angle = 0;
		for (;;)
		{
			if (points.size() == 0)
			{
				break;
			}

			auto X = hull[hull.size() - 1].x;
			auto Y = hull[hull.size() - 1].y;
			best_pt = points[0];
			float best_angle = 3600;

			for (auto& pt : points)
			{
				auto test_angle = angle_value(X, Y, pt.x, pt.y);
				if ((test_angle >= sweep_angle) && (best_angle > test_angle))
				{
					best_angle = test_angle;
					best_pt = pt;
				}
			}

			auto first_angle = angle_value(X, Y, hull[0].x, hull[0].y);
			if ((first_angle >= sweep_angle) && (best_angle >= first_angle))
			{
				break;
			}

			hull.push_back(best_pt);

			points.erase(std::remove(points.begin(), points.end(), best_pt), points.end());

			sweep_angle = best_angle;
		}

		return hull;
	}
}

Clipper2Lib::PathsD Geometry::clip_polygons(std::vector<Polygon>& polygons)
{
	Clipper2Lib::PathsD subj(polygons.size());
	Clipper2Lib::PathsD clip(polygons.size());

	for (const Polygon& polygon : polygons)
	{
		subj.push_back(polygon.to_clipper_path());
		clip.push_back(polygon.to_clipper_path());
	}

	auto solution = Union(subj, clip, Clipper2Lib::FillRule::NonZero);

	return solution;
}

Geometry::Polygon Geometry::to_polygon(const Clipper2Lib::PathD& v)
{
	Polygon polygon = Polygon();
	for (const auto& point: v)
		polygon.add(Vec3(point.x, 0, point.y));
	return polygon;
}

std::vector<Geometry::Polygon> Geometry::to_polygons(const Clipper2Lib::PathsD& v)
{
	std::vector<Polygon> result;
	for (const auto& item : v)
		result.push_back(to_polygon(item));
	return result;
}