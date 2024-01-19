#include "Vector.h"

Vec2 Vec2::zero{ 0.f, 0.f };
Vec3 Vec3::zero{ 0.f, 0.f, 0.f };

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator+(float val) const
{
	return Vec2(this->x + val, this->y + val);
}

void Vec2::operator+=(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
}

void Vec2::operator+=(float f)
{
	this->x += f;
	this->y += f;
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator-(float val) const
{
	return Vec2(this->x - val, this->y - val);
}

void Vec2::operator-=(const Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void Vec2::operator-=(float f)
{
	this->x -= f;
	this->y -= f;
}

Vec2 Vec2::operator*(float val) const
{
	return Vec2(this->x * val, this->y * val);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(this->x * other.x, this->y * other.y);
}

void Vec2::operator*=(const Vec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void Vec2::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
}

Vec2 Vec2::operator/(const Vec2& other) const
{
	return Vec2(this->x / other.x, this->y / other.y);
}

Vec2 Vec2::operator/(float val) const
{
	return Vec2(this->x / val, this->y / val);
}

void Vec2::operator/=(const Vec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

void Vec2::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
}

bool Vec2::operator==(const Vec2& other) const
{
	return Math::NearEqual(other.x, x) && Math::NearEqual(other.y, y);
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
	auto screenSize = renderer->get_renderer_size();

	return
		this->x + extraRadiusCheck >= 0
		&& this->x - extraRadiusCheck <= screenSize.x
		&& this->y + extraRadiusCheck >= 0
		&& this->y - extraRadiusCheck <= screenSize.y;

	return true;
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

float Vec2::distance(const Vec2& seg_start, Vec2& seg_end, bool only_if_on_segment) const
{
	const ProjectionInfo projection = project_on(seg_start, seg_end);
	return !projection.is_on_segment && only_if_on_segment ? FLT_MAX : projection.segment_point.distance(*this);
}

float Vec2::distance_squared(const Vec2& to) const {
	Vec2 delta;

	delta.x = x - to.x;
	delta.y = y - to.y;

	return delta.length_squared();
}

float Vec2::distance_squared(const Vec2& seg_start, Vec2& seg_end, bool only_if_on_segment) const
{
	const ProjectionInfo projection = project_on(seg_start, seg_end);
	return !projection.is_on_segment && only_if_on_segment ? FLT_MAX : projection.segment_point.distance_squared(*this);
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

Vec2 Vec2::perpendicular() const
{
	return Vec2(-y, x);
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

	IntersectionResultVec2 ret;
	ret.intersects = true;
	ret.intersection_point = Vec2((float)(x + (r * deltaBAx)), (float)(y + (r * deltaBAy)));
	return ret;
}

ProjectionInfo Vec2::project_on(const Vec2& segment_start, Vec2& segment_end) const
{
	double x1 = x;
	float y1 = y;
	float x2 = segment_start.x;
	float y2 = segment_start.y;
	float x3 = segment_end.x;
	float y3 = segment_end.y;
	double num1 = (double)x2;
	float num2 = (float)(((x1 - num1) * ((double)x3 - (double)x2) + ((double)y1 - (double)y2) * ((double)y3 - (double)y2)) / (pow((double)x3 - (double)x2, 2.0) + pow((double)y3 - (double)y2, 2.0)));
	Vec2 linePoint{ x2 + num2 * (x3 - x2), y2 + num2 * (y3 - y2) };
	float num3 = (double)num2 >= 0.0 ? ((double)num2 <= 1.0 ? num2 : 1.f) : 0.0f;
	bool num4 = Math::NearEqual(num3, num2);
	return ProjectionInfo(num4 != 0, num4 != 0 ? linePoint : Vec2(x2 + num3 * (x3 - x2), y2 + num3 * (y3 - y2)), linePoint);
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
	Vec3 pos{ x, height, y };
	
	if (height == -1.f)
		pos.y = nav_mesh->get_height_for_position(pos);
	
	return pos;
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

void Vec3::operator+=(const Vec3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vec3::operator+=(float f)
{
	this->x += f;
	this->y += f;
	this->z += f;
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

void Vec3::operator-=(const Vec3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Vec3::operator-=(float f)
{
	this->x -= f;
	this->y -= f;
	this->z -= f;
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

void Vec3::operator*=(const Vec3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

void Vec3::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
}

Vec3 Vec3::operator/(const Vec3& v) const
{
	return Vec3(this->x / v.x, this->y / v.y, this->z / v.z);
}

Vec3 Vec3::operator/(float f) const
{
	return Vec3(this->x / f, this->y / f, this->z / f);
}

void Vec3::operator/=(const Vec3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}

void Vec3::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
}

bool Vec3::operator!=(const Vec3& v) const
{
	return !(*this == v);
}

bool Vec3::operator==(const Vec3& v) const
{
	return Math::NearEqual(v.x, x) && Math::NearEqual(v.y, y) && Math::NearEqual(v.z, z);
}

bool Vec3::is_valid() const
{
	return this->x != 0 && this->z != 0;
}

bool Vec3::is_on_screen(int tolerance) const
{
	Vec2 windowSize{ renderer->get_renderer_size() };

	return this->x + tolerance >= 0 && this->x - tolerance <= windowSize.x &&
		this->y + tolerance >= 0 && this->y - tolerance <= windowSize.y;
}

Vec3 Vec3::set_height(float val)
{
	if (val == FLT_MIN)
		y = nav_mesh->get_height_for_position(*this);
	else
		y = val;

	return *this;
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

	auto theta = atanf(y / x) * (float)M_PI / 180.f;

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

float Vec3::distance(const Vec3& to, bool use_height) const
{
	Vec3 delta;

	delta.x = x - to.x;
	delta.z = z - to.z;

	if (use_height)
		delta.y = y - to.y;

	return delta.length();
}

float Vec3::distance_squared(const Vec3& to, bool use_height) const
{
	Vec3 delta;

	delta.x = x - to.x;
	delta.z = z - to.z;
	
	if (use_height)
		delta.y = y - to.y;

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

Vec2 Vec3::to_screen() const {
	return renderer->world_to_screen(*this);
}

std::string Vec3::to_string() const
{
	return "{ " + std::to_string(x) + " | " + std::to_string(y) + " | " + std::to_string(z) + " }";
}

bool Vec3::is_under_tower(bool ally, bool enemy) const
{
	for (const auto& tower : entities->get_turrets())
	{
		if (!tower->is_alive() || !tower->is_visible() || !tower->is_targetable())
			continue;

		if ((tower->is_ally() && !ally) || (tower->is_enemy() && !enemy))
			continue;

		if (tower->get_position().to_2d().distance(this->to_2d()) <= 900.0f)
			return true;
	}

	return false;
}

bool Vec3::is_on_fountain(bool ally) const
{
	bool isOnEnemyFountain{ local_player->get_team() == GameObjectTeam::Blue ?
			this->x > 13540.0f && this->z > 13470.0f :
			this->x < 1276.0f && this->z < 1344.0f };

	// todo: add aram fountain as well if map is howling abyss

	return ally ? !isOnEnemyFountain : isOnEnemyFountain;
}

bool Math::IsZero(float A)
{
	return fabsf(A) < 1e-6f;
}

bool Math::NearEqual(float A, float B, int maxUlpsDiff)
{
	Float_t uA(A);
	Float_t uB(B);

	if (uA.Negative() != uB.Negative())
	{
		if (A == B)
			return true;
		return false;
	}

	int ulpsDiff = abs(uA.i - uB.i);
	if (ulpsDiff <= maxUlpsDiff)
		return true;
	return false;
}

std::vector<Vec3> Vec3::cut_path(std::vector<Vec3>& path, float distance)
{
	std::vector<Vec3> result;
	auto Distance = distance;

	if (distance < 0)
	{
		path[0] = path[0] + (path[1] - path[0]).normalized() * distance;
		return path;
	}

	for (auto i = 0; i < path.size() - 1; i++)
	{
		auto dist = path[i].distance(path[i + 1]);
		if (dist > Distance)
		{
			result.push_back(path[i] + (path[i + 1] - path[i]).normalized() * Distance);
			for (auto j = i + 1; j < path.size(); j++)
			{
				result.push_back(path[j]);
			}
			break;
		}
		Distance -= dist;
	}
	return result.size() > 0 ? result : std::vector<Vec3>{ path.back() };
}

float Vec3::path_length(const std::vector<Vec3>& path)
{
	float distance = 0.0f;
	for (int i = 0; i < path.size() - 1; i++)
	{
		distance += path[i].distance(path[i + 1]);
	}
	return distance;
}

Vec3MovementCollision Vec3::vec3_movement_collision(const Vec3& start_point1, const Vec3& end_point1, float v1, const Vec3& start_point2, float v2, float delay)
{
	auto sP1x = start_point1.x;
	auto sP1y = start_point1.z;
	auto eP1x = end_point1.x;
	auto eP1y = end_point1.z;
	auto sP2x = start_point2.x;
	auto sP2y = start_point2.z;

	float d = eP1x - sP1x, e = eP1y - sP1y;
	float dist = (float)sqrt(d * d + e * e);
	float t1 = NAN;
	float S = abs(dist) > FLT_EPSILON ? v1 * d / dist : 0.f,
		K = (abs(dist) > FLT_EPSILON) ? v1 * e / dist : 0.f;

	float r = sP2x - sP1x, j = sP2y - sP1y;
	auto c = r * r + j * j;

	if (dist > 0.f)
	{
		if (abs(v1 - FLT_MAX) < FLT_EPSILON)
		{
			auto t = dist / v1;
			t1 = v2 * t >= 0.f ? t : NAN;
		}
		else if (abs(v2 - FLT_MAX) < FLT_EPSILON)
		{
			t1 = 0.f;
		}
		else
		{
			float a = S * S + K * K - v2 * v2, b = -r * S - j * K;

			if (abs(a) < FLT_EPSILON)
			{
				if (abs(b) < FLT_EPSILON)
				{
					t1 = (abs(c) < FLT_EPSILON) ? 0.f : NAN;
				}
				else
				{
					auto t = -c / (2 * b);
					t1 = (v2 * t >= 0.f) ? t : NAN;
				}
			}
			else
			{
				auto sqr = b * b - a * c;
				if (sqr >= 0)
				{
					auto nom = (float)sqrt(sqr);
					auto t = (-nom - b) / a;
					t1 = v2 * t >= 0.f ? t : NAN;
					t = (nom - b) / a;
					auto t2 = (v2 * t >= 0.f) ? t : NAN;

					if (!isnan(t2) && !isnan(t1))
					{
						if (t1 >= delay && t2 >= delay)
						{
							t1 = fmin(t1, t2);
						}
						else if (t2 >= delay)
						{
							t1 = t2;
						}
					}
				}
			}
		}
	}
	else if (abs(dist) < FLT_EPSILON)
	{
		t1 = 0.f;
	}


	return Vec3MovementCollision{ t1, (!isnan(t1)) ? Vec3(sP1x + S * t1, 0, sP1y + K * t1) : Vec3(0, 0, 0) };
}

Vec2MovementCollision Vec2::vec2_movement_collision(const Vec2& start_point1, const Vec2& end_point1, float v1, const Vec2& start_point2, float v2, float delay)
{
	if (!start_point1.is_valid() || !end_point1.is_valid())
		return { };
	float x1 = start_point1.x;
	float y1 = start_point1.y;
	float x2 = end_point1.x;
	double y2 = end_point1.y;
	float x3 = start_point2.x;
	float y3 = start_point2.y;
	float num1 = x2 - x1;
	double num2 = (double)y1;
	float num3 = (float)(y2 - num2);
	float num4 = (float)sqrt((double)num1 * (double)num1 + (double)num3 * (double)num3);
	float num5 = 0.f / 0.f;
	float num6 = (double)abs(num4) > 1.4012984643248171E-45 ? v1 * num1 / num4 : 0.0f;
	float num7 = (double)abs(num4) > 1.4012984643248171E-45 ? v1 * num3 / num4 : 0.0f;
	float num8 = x3 - x1;
	float num9 = y3 - y1;
	float num10 = (float)((double)num8 * (double)num8 + (double)num9 * (double)num9);
	if ((double)num4 > 0.0)
	{
		if (v1 == FLT_MAX)
		{
			float num11 = num4 / v1;
			num5 = (double)v2 * (double)num11 >= 0.0 ? num11 : 0.f / 0.f;
		}
		else if (v2 == FLT_MAX)
		{
			num5 = 0.0f;
		}
		else
		{
			float num12 = (float)((double)num6 * (double)num6 + (double)num7 * (double)num7 - (double)v2 * (double)v2);
			float num13 = (float)(-(double)num8 * (double)num6 - (double)num9 * (double)num7);
			if ((double)abs(num12) < 1.4012984643248171E-45)
			{
				if ((double)abs(num13) < 1.4012984643248171E-45)
				{
					num5 = (double)abs(num10) < 1.4012984643248171E-45 ? 0.0f : 0.f / 0.f;
				}
				else
				{
					float num14 = (float)(-(double)num10 / (2.0 * (double)num13));
					num5 = (double)v2 * (double)num14 >= 0.0 ? num14 : 0.f / 0.f;
				}
			}
			else
			{
				float d = (float)((double)num13 * (double)num13 - (double)num12 * (double)num10);
				if ((double)d >= 0.0)
				{
					double num15 = sqrt((double)d);
					float num16 = ((float)-num15 - num13) / num12;
					num5 = (double)v2 * (double)num16 >= 0.0 ? num16 : 0.f / 0.f;
					float num17 = ((float)num15 - num13) / num12;
					float num18 = (double)v2 * (double)num17 >= 0.0 ? num17 : 0.f / 0.f;
					if (!isnan(num18) && !isnan(num5))
					{
						if ((double)num5 >= (double)delay && (double)num18 >= (double)delay)
							num5 = std::min(num5, num18);
						else if ((double)num18 >= (double)delay)
							num5 = num18;
					}
				}
			}
		}
	}
	else if ((double)abs(num4) < 1.4012984643248171E-45)
		num5 = 0.0f;
	return { num5, !isnan(num5) ? Vec2(x1 + num6 * num5, y1 + num7 * num5) : Vec2() };
}

float Vec2::path_length(const std::vector<Vec2>& path)
{
	float distance = 0.0f;
	for (int i = 0; i < path.size() - 1; i++)
	{
		distance += path[i].distance(path[i + 1]);
	}
	return distance;
}

Vec3 Vec3::position_after(const std::vector<Vec3>& self, int t, int speed, int delay)
{
	int distance = fmax(0, t - delay) * speed / 1000;

	for (int i = 0; i <= self.size() - 2; i++)
	{
		Vec3 from = self[i];
		Vec3 to = self[i + 1];
		int d = (int)to.distance(from);
		if (d > distance)
		{
			return from + (to - from).normalized() * distance;
		}
		distance -= d;
	}

	return self[self.size() - 1];
}
