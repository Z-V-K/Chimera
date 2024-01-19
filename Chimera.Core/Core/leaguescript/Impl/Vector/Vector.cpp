#include "../pch.h"
#include "../Impl/Vector/Vector.h"
#include "../Framework/Rendering/r3dRenderer/r3dRenderer.h"

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator+(float val) const
{
	return Vec2(this->x + val, this->y + val);
}

Vec2 Vec2::operator+=(const Vec2& v) const
{
	return *this + v;
}

Vec2 Vec2::operator+=(float f) const
{
	return *this + f;
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator-(float val) const
{
	return Vec2(this->x - val, this->y - val);
}

Vec2 Vec2::operator-=(const Vec2& v) const
{
	return *this - v;
}

Vec2 Vec2::operator-=(float f) const
{
	return *this - f;
}

Vec2 Vec2::operator*(float val) const
{
	return Vec2(this->x * val, this->y * val);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(this->x * other.x, this->y * other.y);
}

Vec2 Vec2::operator*=(const Vec2& v) const
{
	return *this * v;
}

Vec2 Vec2::operator*=(float f) const
{
	return *this * f;
}

Vec2 Vec2::operator/(const Vec2& other) const
{
	return Vec2(this->x / other.x, this->y / other.y);
}

Vec2 Vec2::operator/(float val) const
{
	return Vec2(this->x / val, this->y / val);
}

Vec2 Vec2::operator/=(const Vec2& v) const
{
	return *this / v;
}

Vec2 Vec2::operator/=(float f) const
{
	return *this * f;
}

bool Vec2::operator==(const Vec2& other) const
{
	return math::NearEqual(other.x, x) && math::NearEqual(other.y, y);
}

bool Vec2::operator!=(const Vec2& v) const
{
	return !(*this == v);
}

bool Vec2::is_valid() const
{
	return x != 0 && y != 0;
}

bool Vec2::is_visible_on_screen() const
{
	auto extraRadiusCheck = 25.f;
	auto screenSize = r3dRenderer::instance()->get_renderer_size();

	return
		this->x + extraRadiusCheck >= 0
		&& this->x - extraRadiusCheck <= screenSize.x
		&& this->y + extraRadiusCheck >= 0
		&& this->y - extraRadiusCheck <= screenSize.y;
}

float Vec2::length() const {
	return sqrtf(x * x + y * y);
}

float Vec2::length_squared() const {
	return this->x * this->x + this->y * this->y;
}

float Vec2::distance(const Vec2& o) const {
	return sqrtf(powf(x - o.x, 2) + powf(y - o.y, 2));
}

float Vec2::distance_squared(const Vec2& to) const {
	Vec2 delta;

	delta.x = x - to.x;
	delta.y = y - to.y;

	return delta.length_squared();
}

Vec2 Vec2::v_scale(const Vec2& s) const {
	return Vec2(x * s.x, y * s.y);
}

Vec2 Vec2::scale(float s) const {
	return Vec2(x * s, y * s);
}

Vec2 Vec2::normalized() const {
	const auto l = length();
	if (l != 0)
	{
		auto const inv = 1.0f / l;
		return { this->x * inv, this->y * inv };
	}

	return *this;
}

Vec2 Vec2::clone() const {
	return Vec2(x, y);
}

float Vec2::polar() const
{
	if (fabs(x - 0) <= FLT_EPSILON)
	{
		return (y > 0.f) ? 90.f : (y < 0.f) ? 270.f : 0.f;
	}

	auto theta = (float)(atanf(y / x) * (180 / M_PI));
	if (x < 0.f)
	{
		theta += 180;
	}

	if (theta < 0.f)
	{
		theta += 360;
	}

	return theta;
}

float Vec2::cross_product(const Vec2& other) const
{
	return other.y * this->x - other.x * this->y;
}

float Vec2::angle_between(const Vec2& o) const
{
	float theta = polar() - o.polar();
	if (theta < 0)
	{
		theta = theta + 360;
	}

	if (theta > 180)
	{
		theta = 360 - theta;
	}

	return theta;
}

IntersectionResultVec2 Vec2::intersection(const Vec2& line_segment1_end, Vec2& line_segment2_start, Vec2& line_segment2_end) const
{
	float deltaACy = y - line_segment2_start.y;
	float deltaDCx = line_segment2_end.x - line_segment2_start.x;
	float deltaACx = x - line_segment2_start.x;
	float deltaDCy = line_segment2_end.y - line_segment2_start.y;
	float deltaBAx = line_segment1_end.x - x;
	float deltaBAy = line_segment1_end.y - y;

	auto denominator = (deltaBAx * deltaDCy) - (deltaBAy * deltaDCx);
	auto numerator = (deltaACy * deltaDCx) - (deltaACx * deltaDCy);

	if (fabs(denominator) < FLT_EPSILON)
	{
		if (fabs(numerator) < FLT_EPSILON)
		{
			// collinear. Potentially infinite intersection points.
			// Check and return one of them.
			if (x >= line_segment2_start.x && x <= line_segment2_end.x)
			{
				return IntersectionResultVec2{ true, *this };
			}

			if (line_segment2_start.x >= x && line_segment2_start.x <= line_segment1_end.x)
			{
				return IntersectionResultVec2{ true, line_segment2_start };
			}

			return IntersectionResultVec2{ 1 };
		}

		// parallel
		return IntersectionResultVec2{ 2 };
	}

	auto r = numerator / denominator;
	if (r < 0 || r > 1)
	{
		return IntersectionResultVec2{ 3 };
	}

	auto s = ((deltaACy * deltaBAx) - (deltaACx * deltaBAy)) / denominator;
	if (s < 0 || s > 1)
	{
		return IntersectionResultVec2{ 4 };
	}

	return IntersectionResultVec2(
		true,
		Vec2(
			(float)(x + (r * deltaBAx)),
			(float)(y + (r * deltaBAy))));
}

ProjectionInfo Vec2::project_on(const Vec2& segment_start, Vec2& segment_end) const
{
	auto cx = x;
	auto cy = y;
	auto ax = segment_start.x;
	auto ay = segment_start.y;
	auto bx = segment_end.x;
	auto by = segment_end.y;
	auto rL = (((cx - ax) * (bx - ax)) + ((cy - ay) * (by - ay)))
		/ ((float)pow(bx - ax, 2) + (float)pow(by - ay, 2));
	auto pointLine = Vec2(ax + (rL * (bx - ax)), ay + (rL * (by - ay)));
	float rS;
	if (rL < 0)
	{
		rS = 0;
	}
	else if (rL > 1)
	{
		rS = 1;
	}
	else
	{
		rS = rL;
	}

	bool isOnSegment = rS == rL;
	auto pointSegment = isOnSegment ? pointLine : Vec2(ax + (rS * (bx - ax)), ay + (rS * (by - ay)));
	return ProjectionInfo(isOnSegment, pointSegment, pointLine);
}

Vec2 Vec2::append(const Vec2& pos1, Vec2& pos2, float dist) const
{
	return pos2 + (pos2 - pos1).normalized() * dist;
}

Vec2 Vec2::rotated(float angle) const
{
	auto const c = cosf(angle);
	auto const s = sinf(angle);

	return { static_cast<float>(x * c - y * s), static_cast<float>(y * c + x * s) };
}

Vec2 Vec2::extend(const Vec2& to, float distance) const
{
	auto from = *this;
	auto result = from + (to - from).normalized() * Vec2(distance, distance);
	return result;
}

Vec3 Vec2::to_3d(float height) const
{
	return Vec3(x, height, y);
}

std::string Vec2::to_string() const
{
	return "{ " + std::to_string(x) + " | " + std::to_string(y) + " }";
}

Vec3 Vec3::operator+(const Vec3& v) const
{
	Vec3 result(this->x + v.x, this->y + v.y, this->z + v.z);
	return result;
}

Vec3 Vec3::operator+(float f) const
{
	Vec3 result(this->x + f, this->y + f, this->z + f);
	return result;
}

Vec3 Vec3::operator+=(const Vec3& v) const
{
	return *this + v;
}

Vec3 Vec3::operator+=(float f) const
{
	return *this + f;
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	Vec3 result(this->x - v.x, this->y - v.y, this->z - v.z);
	return result;
}

Vec3 Vec3::operator-(float f) const
{
	Vec3 result(this->x - f, this->y - f, this->z - f);
	return result;
}

Vec3 Vec3::operator-=(const Vec3& v) const
{
	return *this - v;
}

Vec3 Vec3::operator-=(float f) const
{
	return *this - f;
}

Vec3 Vec3::operator*(const Vec3& v) const
{
	Vec3 result(this->x * v.x, this->y * v.y, this->z * v.z);
	return result;
}

Vec3 Vec3::operator*(float f) const
{
	Vec3 result(this->x * f, this->y * f, this->z * f);
	return result;
}

Vec3 Vec3::operator*=(const Vec3& v) const
{
	return *this * v;
}

Vec3 Vec3::operator*=(float f) const
{
	return *this * f;
}

Vec3 Vec3::operator/(const Vec3& v) const
{
	return Vec3(this->x / v.x, this->y / v.y, this->z / v.z);
}

Vec3 Vec3::operator/(float f) const
{
	return Vec3(this->x / f, this->y / f, this->z / f);
}

Vec3 Vec3::operator/=(const Vec3& v) const
{
	return *this / v;
}

Vec3 Vec3::operator/=(float f) const
{
	return *this / f;
}

bool Vec3::operator!=(const Vec3& v) const
{
	return !(*this == v);
}

bool Vec3::operator==(const Vec3& v) const
{
	return math::NearEqual(v.x, x) && math::NearEqual(v.y, y) && math::NearEqual(v.z, z);
}

bool Vec3::is_valid() const
{
	return this->x != 0/* && this->y != 0*/ && this->z != 0;
}

bool Vec3::is_on_screen(int tolerance) const
{
	r3dRenderer* renderer{ r3dRenderer::instance()->instance() };

	Vec2 onScreen{ renderer->world_to_screen(*this) };
	Vec2 windowSize{ renderer->get_renderer_size() };

	return onScreen.x + tolerance >= 0 && onScreen.x - tolerance <= windowSize.x &&
		onScreen.y + tolerance >= 0 && onScreen.y - tolerance <= windowSize.y;
}

Vec3 Vec3::set_height(float val) const // TODO; getHeightForPos
{
	//if (val == FLT_MIN) const
	//	y = NavMesh::GetHeightForPosition(*this);
	//else
		//y = val;

	return Vec3(this->x, val, this->z);
}

Vec3 Vec3::switch_yz() const
{
	return Vec3(this->x, this->z, this->y);
}

Vec3 Vec3::negate() const
{
	return Vec3(-this->x, -this->y, -this->z);
}

float Vec3::dot_product(const Vec3& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

float Vec3::cross_product(const Vec3& other) const
{
	return other.y * this->x - other.x * this->y;
}

float Vec3::polar() const
{
	if (fabs(x) < FLT_EPSILON)
	{
		if (y > 0.f)
		{
			return 90.f;
		}

		return y < 0.f ? 270.f : 0.f;
	}

	auto theta = atanf(y / x) * (float) M_PI / 180.f;

	if (x < 0.f)
	{
		theta += 180.f;
	}
	if (theta < 0.f)
	{
		theta += 360.f;
	}

	return theta;
}

float Vec3::angle_between(const Vec3& other) const
{
	auto v2d = other.to_2d();
	return to_2d().angle_between(v2d);
}

bool Vec3::close(float a, float b, float eps) const
{
	if (fabs(eps) < FLT_EPSILON)
	{
		eps = static_cast<float>(1e-9);
	}
	return fabs(a - b) <= eps;
}

// Expects angle in radians!
Vec3 Vec3::rotated(float angle) const
{
	auto const c = cosf(angle);
	auto const s = sinf(angle);

	return { static_cast<float>(x * c - z * s), y, static_cast<float>(z * c + x * s) };
}

Vec3 Vec3::perpendicular() const
{
	return { -z,y,x };
}

Vec3 Vec3::append(const Vec3& pos1, Vec3& pos2, float dist) const
{
	return pos2 + (pos2 - pos1).normalized() * dist;
}

Vec3 Vec3::clone() const
{
	return Vec3(x, y, z);
}

float Vec3::length() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vec3::length_squared() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vec3 Vec3::normalized() const
{
	auto const length = this->length();
	if (length != 0)
	{
		auto const inv = 1.0f / length;
		return { this->x * inv, this->y * inv, this->z * inv };
	}

	return *this;
}

float Vec3::distance(const Vec3& to) const
{
	Vec3 delta;

	delta.x = x - to.x;
	delta.y = y - to.y;
	delta.z = z - to.z;

	return delta.length();
}

float Vec3::distance_squared(const Vec3& to) const
{
	Vec3 delta;

	delta.x = x - to.x;
	delta.y = y - to.y;
	delta.y = z - to.z;

	return delta.length_squared();
}

Vec3 Vec3::extend(const Vec3& to, float distance) const
{
	auto from = *this;
	auto result = from + (to - from).normalized() * distance;
	return result;
}

Vec3 Vec3::scale(float s) const
{
	return Vec3(x * s, y * s, z * s);
}

Vec3 Vec3::rotate(const Vec3& startPos, float theta) const
{
	float dx = this->x - startPos.x;
	float dz = this->z - startPos.z;

	float px = dx * cosf(theta) - dz * sinf(theta);
	float pz = dx * sinf(theta) + dz * cosf(theta);
	return { px + startPos.x, this->y, pz + startPos.z };
}

Vec3 Vec3::rotate_x(float angle) const {
	return Vec3(
		x,
		y * cosf(angle) - z * sinf(angle),
		y * sinf(angle) + z * cosf(angle)
	);
}

Vec3 Vec3::rotate_y(float angle) const {
	return Vec3(
		x * cosf(angle) + z * sinf(angle),
		y,
		-x * sinf(angle) + z * cosf(angle)
	);
}

Vec3 Vec3::rotate_z(float angle) const {
	return Vec3(
		x * cosf(angle) - y * sinf(angle),
		x * sinf(angle) + y * cosf(angle),
		z
	);
}

Vec2 Vec3::to_2d() const {
	return Vec2(x, z);
}

std::string Vec3::to_string() const
{
	return "{ " + std::to_string(x) + " | " + std::to_string(y) + " | " + std::to_string(z) + " }";
}

bool math::IsZero(float A)
{
	return fabsf(A) < 1e-6f;
}

bool math::NearEqual(float A, float B, int maxUlpsDiff)
{
	Float_t uA(A);
	Float_t uB(B);

	// Different signs means they do not match.
	if (uA.Negative() != uB.Negative())
	{
		// Check for equality to make sure +0==-0
		if (A == B)
			return true;
		return false;
	}

	// Find the difference in ULPs.
	int ulpsDiff = abs(uA.i - uB.i);
	if (ulpsDiff <= maxUlpsDiff)
		return true;
	return false;
}