#pragma once

#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

namespace Math
{
	/*  See
		https://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
		for the potential portability problems with the union and bit-fields below.
	*/
	union Float_t
	{
		Float_t(float num = 0.0f) : f(num) {}
		// Portable extraction of components.
		[[nodiscard]] bool Negative() const { return i < 0; }
		[[nodiscard]] int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
		[[nodiscard]] int32_t RawExponent() const { return (i >> 23) & 0xFF; }

		int32_t i;
		float f;
#ifdef _DEBUG
		struct
		{   // Bitfields for exploration. Do not use in production code.
			uint32_t mantissa : 23;
			uint32_t exponent : 8;
			uint32_t sign : 1;
		} parts;
#endif
	};

	bool IsZero(float A);
	bool NearEqual(float A, float B, int maxUlpsDiff = 4);
}

struct IntersectionResultVec2;
struct IntersectionResultVec3;
struct ProjectionInfo;
struct Vec2MovementCollision;
struct Vec3MovementCollision;
class Vec3;

class Vec2
{
public:
	float x, y;
	Vec2() { x = y = 0.f; };
	Vec2(float x, float y) : x(x), y(y) {};

	[[nodiscard]] Vec2					 operator+(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator+(float f) const;
	 void								 operator+=(const Vec2& v);
	 void								 operator+=(float f);
	[[nodiscard]] Vec2					 operator-(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator-(float f) const;
	 void								 operator-=(const Vec2& v);
	 void								 operator-=(float f);
	[[nodiscard]] Vec2					 operator*(float f) const;
	[[nodiscard]] Vec2					 operator*(const Vec2& v) const;
	 void								 operator*=(const Vec2& v);
	 void								 operator*=(float f);
	[[nodiscard]] Vec2					 operator/(const Vec2& v) const;
	[[nodiscard]] Vec2					 operator/(float f) const;
	 void								 operator/=(const Vec2& v);
	 void								 operator/=(float f);
	[[nodiscard]] bool					 operator==(const Vec2& v) const;
	[[nodiscard]] bool					 operator!=(const Vec2& v) const;

	[[nodiscard]] bool					 is_valid() const;
	[[nodiscard]] bool					 is_visible_on_screen() const;
	[[nodiscard]] float					 length() const;
	[[nodiscard]] float					 length_squared() const;
	[[nodiscard]] float					 distance(const Vec2& o) const;
	[[nodiscard]] float					 distance(const Vec2& seg_start, Vec2& seg_end, bool only_if_on_segment) const;
	[[nodiscard]] float					 distance_squared(const Vec2& o) const;
	[[nodiscard]] float					 distance_squared(const Vec2& seg_start, Vec2& seg_end, bool only_if_on_segment = false) const;
	[[nodiscard]] Vec2					 v_scale(const Vec2& s) const;
	[[nodiscard]] Vec2					 scale(float s) const;
	[[nodiscard]] Vec2					 normalized() const;
	[[nodiscard]] Vec2					 perpendicular() const;
	[[nodiscard]] Vec2					 append(const Vec2& pos1, Vec2& pos2, float dist) const;
	[[nodiscard]] Vec2					 rotated(float angle) const;
	[[nodiscard]] Vec2					 clone() const;
	[[nodiscard]] float					 polar() const;
	[[nodiscard]] float					 cross_product(const Vec2& other) const;
	[[nodiscard]] float					 angle_between(const Vec2& o) const;
	[[nodiscard]] IntersectionResultVec2 intersection(const Vec2& line_segment1_end, Vec2& line_segment2_start, Vec2& line_segment2_end) const;
	[[nodiscard]] ProjectionInfo		 project_on(const Vec2& segment_start, Vec2& segment_end) const;
	[[nodiscard]] Vec2					 extend(const Vec2& to, float distance) const;
	[[nodiscard]] Vec3					 to_3d(float height = -1.f) const;
	[[nodiscard]] std::string			 to_string() const;

	[[nodiscard]] static Vec2MovementCollision vec2_movement_collision(const Vec2& start_point1, const Vec2& end_point1, float v1, const Vec2& start_point2, float v2, float delay);
	[[nodiscard]] static float path_length(const std::vector<Vec2>& path);

	static Vec2 zero;
};

class Vec3
{
public:
	float x, y, z;
	Vec3() { x = y = z = 0.f; };
	Vec3(float x, float y, float z = 0) : x(x), y(y), z(z) {};

	[[nodiscard]] Vec3					operator+(const Vec3& v) const;
	[[nodiscard]] Vec3					operator+(float f) const;
	 void								operator+=(const Vec3& v);
	 void								operator+=(float f);
	[[nodiscard]] Vec3					operator-(const Vec3& v) const;
	[[nodiscard]] Vec3					operator-(float f) const;
	 void								operator-=(const Vec3& v);
	 void								operator-=(float f);
	[[nodiscard]] Vec3					operator*(const Vec3& v) const;
	[[nodiscard]] Vec3					operator*(float f) const;
	 void								operator*=(const Vec3& v);
	 void								operator*=(float f);
	[[nodiscard]] Vec3					operator/(const Vec3& v) const;
	[[nodiscard]] Vec3					operator/(float f) const;
	 void								operator/=(const Vec3& v);
	 void								operator/=(float f);
	[[nodiscard]] bool					operator!=(const Vec3& v) const;
	[[nodiscard]] bool					operator==(const Vec3& v) const;

	[[nodiscard]] bool					is_valid() const;
	[[nodiscard]] bool					is_on_screen(int tolerance = 0) const;
	[[nodiscard]] Vec3					switch_yz() const;
	[[nodiscard]] Vec3					negate() const;
	[[nodiscard]] float					dot_product(const Vec3& other) const;
	[[nodiscard]] float					cross_product(const Vec3& other) const;
	[[nodiscard]] float					polar() const;
	[[nodiscard]] float					angle_between(const Vec3& other) const;
	[[nodiscard]] bool					close(float a, float b, float eps) const;
	[[nodiscard]] Vec3					rotated(float angle) const;
	[[nodiscard]] Vec3					perpendicular() const;
	[[nodiscard]] Vec3					append(const Vec3& pos1, Vec3& pos2, float dist) const;
	[[nodiscard]] Vec3					clone() const;
	[[nodiscard]] float					length() const;
	[[nodiscard]] float					length_squared() const;
	[[nodiscard]] float					distance(const Vec3& to, bool use_height = false) const;
	[[nodiscard]] float					distance_squared(const Vec3& to, bool use_height = false) const;
	[[nodiscard]] Vec3					extend(const Vec3& to, float distance) const;
	[[nodiscard]] Vec3					scale(float s) const;
	[[nodiscard]] Vec3					rotate(const Vec3& startPos, float theta) const;
	[[nodiscard]] Vec3					rotate_x(float angle) const;
	[[nodiscard]] Vec3					rotate_y(float angle) const;
	[[nodiscard]] Vec3					rotate_z(float angle) const;
	[[nodiscard]] Vec3					normalized() const;
	[[nodiscard]] Vec3					set_height(float val = FLT_MIN);
	[[nodiscard]] Vec2					to_2d() const;
	[[nodiscard]] Vec2					to_screen() const;
	[[nodiscard]] std::string			to_string() const;

	[[nodiscard]] bool					is_under_tower(bool ally, bool enemy) const;
	[[nodiscard]] bool					is_on_fountain(bool ally = false) const;

	[[nodiscard]] static std::vector<Vec3> cut_path(std::vector<Vec3>& path, float distance);
	[[nodiscard]] static float path_length(const std::vector<Vec3>& path);
	[[nodiscard]] static Vec3MovementCollision vec3_movement_collision(const Vec3& start_point1, const Vec3& end_point1, float v1, const Vec3& start_point2, float v2, float delay);
	[[nodiscard]] static Vec3 position_after(const std::vector<Vec3>& self, int t, int speed, int delay);

	static Vec3 zero;
};

class Vec4
{
public:
	float x, y, z, w;
};

struct ProjectionInfo
{
	ProjectionInfo(bool on_segment, const Vec2& seg_point, const Vec2& line_point) :
		is_on_segment(on_segment),
		segment_point(seg_point),
		line_point(line_point)
	{ }

	bool is_on_segment;
	Vec2 segment_point;
	Vec2 line_point;
};

struct IntersectionResultVec2
{
	int intersects;
	Vec2 intersection_point;
};

struct IntersectionResultVec3
{
	bool intersects;
	Vec3 intersection_point;
};

struct Vec3MovementCollision
{
	float t;
	Vec3 pos;
};

struct Vec2MovementCollision
{
	float t;
	Vec2 pos;
};