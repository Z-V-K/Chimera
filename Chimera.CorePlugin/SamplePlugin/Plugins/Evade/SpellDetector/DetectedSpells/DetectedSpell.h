#pragma once
#include "../../../../SDK/Geometry.h"

struct EvadeSpellData;

struct DetectedSpell
{
	DetectedSpell(EvadeSpellData* spell_data, const Vec2& start_pos, const Vec2& end_pos) :
		spell_data(spell_data),
		original_start_pos(start_pos),
		original_end_pos(end_pos)
	{

	}

	virtual ~DetectedSpell() = default;

	EvadeSpellData* spell_data = nullptr;

	GameObject* missile = nullptr;
	GameObject* source = nullptr;
	GameObject* target = nullptr;

	Geometry::Polygon polygon;
	Geometry::Polygon visual_polygon;

	Vec2 original_start_pos;
	Vec2 original_end_pos;

	Vec2 cached_start_pos;
	Vec2 cached_end_pos;
	float cached_radius;

	Vec2 direction;

	Vec2 get_start_pos();
	Vec2 get_end_pos();
	float get_range();
	float get_radius();

	float cast_time = 0.f;
	float end_time = 0.f;

	bool is_colliding(const Vec2& pos, float delay);
	float displacement_after_time(float delay);
	Vec2 pos_after_time(float delay);
	bool is_path_dangerous(const Vec3& start, const Vec3& end, float movement_speed, float time);

	virtual bool update_polygon() = 0;
};
