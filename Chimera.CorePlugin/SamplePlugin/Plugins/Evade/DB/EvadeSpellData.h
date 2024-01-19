#pragma once
#include "../../../SDK/Geometry.h"

enum class EvadeSpellType
{
	Line,
	MissileLine,
	Circle,
	Ring,
	Cone,
	CustomPolygon
};

enum class DangerLevel
{
	Low = 1,
	Medium,
	High,
	VeryHigh,
	Extreme
};

struct DetectedSpell;

#ifndef ADD_SPELL_DATA
#define ADD_SPELL_DATA(TYPE, NAME) TYPE NAME = { }; EvadeSpellData* set_##NAME( const TYPE& NAME ) { this->NAME = NAME; return this; }
#define ADD_SPELL_DATA_D(TYPE, NAME, DEFAULT) TYPE NAME = DEFAULT; EvadeSpellData* set_##NAME( const TYPE& NAME ) { this->NAME = NAME; return this; }
#endif

struct EvadeSpellData
{
	std::function<float(DetectedSpell*)> range						 = [] (DetectedSpell* spell) { return 0.f; };
	std::function<float(DetectedSpell*)> delay						 = [] (DetectedSpell* spell) { return .25f; };
	std::function<float(DetectedSpell*)> duration					 = [] (DetectedSpell* spell) { return 0.f; };
	std::function<float(DetectedSpell*)> radius						 = [] (DetectedSpell* spell) { return 0.f; };
	std::function<float(DetectedSpell*)> missile_speed				 = [] (DetectedSpell* spell) { return FLT_MAX; };
	std::function<float(DetectedSpell*)> end_time					 = [] (DetectedSpell* spell) { return 0.f;};
	std::function<int(GameObject*, SpellCastInfo*)> multiple_number	 = [] (GameObject*, SpellCastInfo*) { return 1;};
	std::function<float(GameObject*, SpellCastInfo*)> multiple_angle = [] (GameObject*, SpellCastInfo*) { return 0.f;};
	std::function<DangerLevel(DetectedSpell*)> danger_level			 = [] (DetectedSpell* spell) { return DangerLevel::Medium; };

	std::function<void(SpellCastInfo*)> on_process_spell = [](SpellCastInfo*) { };
	std::function<void(DetectedSpell*)> on_create_object = [](DetectedSpell*) { };
	std::function<void(DetectedSpell*)> on_assign_object = [](DetectedSpell*) { };

	std::function<Vec2(DetectedSpell*)> start_position = [](DetectedSpell*) { return Vec2(); };
	std::function<Vec2(DetectedSpell*)> end_position = [](DetectedSpell*) { return Vec2(); };

	std::function<Geometry::Polygon(DetectedSpell*)> custom_polygon = nullptr;
	std::function<Geometry::Polygon(DetectedSpell*)> end_explosion = nullptr;

	ADD_SPELL_DATA_D(EvadeSpellType, type, EvadeSpellType::Line)
	ADD_SPELL_DATA_D(bool, skip_distance_check, false)
	ADD_SPELL_DATA_D(bool, skip_angle_check, false)

	ADD_SPELL_DATA(float, perpendicular_length)
	ADD_SPELL_DATA(float, extra_range)
	ADD_SPELL_DATA(float, ring_radius)
	ADD_SPELL_DATA(float, missile_acceleration)
	ADD_SPELL_DATA(float, missile_min_speed)
	ADD_SPELL_DATA(float, missile_max_speed)
	ADD_SPELL_DATA(float, offset_start)
	ADD_SPELL_DATA(float, min_range)

	ADD_SPELL_DATA_D(bool, is_enabled, true)
	ADD_SPELL_DATA(bool, is_range_fixed)
	ADD_SPELL_DATA(bool, is_perpendicular)
	ADD_SPELL_DATA(bool, is_inverted)
	ADD_SPELL_DATA(bool, is_dash)
	ADD_SPELL_DATA(bool, is_trap)
	ADD_SPELL_DATA(bool, is_range_limited)
	ADD_SPELL_DATA(bool, is_range_min)
	ADD_SPELL_DATA(bool, is_dangerous)
	ADD_SPELL_DATA(bool, is_hard_cc)
	ADD_SPELL_DATA(bool, is_start_pos_updated_on_flash)
	ADD_SPELL_DATA(bool, is_start_pos_from_unit)
	ADD_SPELL_DATA(bool, is_end_pos_to_unit)
	ADD_SPELL_DATA(bool, add_bounding)
	ADD_SPELL_DATA(bool, follow_cast_direction)
	ADD_SPELL_DATA(bool, has_end_explosion)

	ADD_SPELL_DATA(CharacterHash, hero_hash)
	ADD_SPELL_DATA(std::vector<CollisionObject>, collision_objects)
	ADD_SPELL_DATA(std::vector<uint32_t>, spell_hashes)
	ADD_SPELL_DATA(std::vector<uint32_t>, particle_hashes)
	ADD_SPELL_DATA(std::vector<std::string>, object_names)

	const char* menu_name;

	EvadeSpellData(CharacterHash hero_hash, const char* menu_name) : hero_hash(hero_hash), menu_name(menu_name) { }

	EvadeSpellData* set_range				(const std::function<float(DetectedSpell*)>& f) { range = f; return this; }
	EvadeSpellData* set_range				(float f)						  { range = [f] (DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_delay			(const std::function<float(DetectedSpell*)>& f) { delay = f; return this; }
	EvadeSpellData* set_delay			(float f)						  { delay = [f](DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_duration(const std::function<float(DetectedSpell*)>& f) { duration = f; return this; }
	EvadeSpellData* set_duration(float f) { duration = [f](DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_radius				(const std::function<float(DetectedSpell*)>& f) { radius = f; return this; }
	EvadeSpellData* set_radius				(float f)						  { radius = [f](DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_missile_speed		(const std::function<float(DetectedSpell*)>& f) { missile_speed = f; return this; }
	EvadeSpellData* set_missile_speed		(float f)						  { missile_speed = [f](DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_end_time			(const std::function<float(DetectedSpell*)>& f) { end_time = f; return this; }
	EvadeSpellData* set_end_time			(float f)						  { end_time = [f](DetectedSpell* spell) { return f; }; return this; }

	EvadeSpellData* set_multiple_angle(const std::function<float(GameObject*, SpellCastInfo*)>& f) { multiple_angle = f; return this; }
	EvadeSpellData* set_multiple_angle(float f) { multiple_angle = [f](GameObject*, SpellCastInfo* spell) { return f; }; return this; }

	EvadeSpellData* set_multiple_number(const std::function<int(GameObject*, SpellCastInfo*)>& f) { multiple_number = f; return this; }
	EvadeSpellData* set_multiple_number(int f) { multiple_number = [f](GameObject*, SpellCastInfo* spell) { return f; }; return this; }

	EvadeSpellData* set_danger_level(const std::function<DangerLevel(DetectedSpell*)> f) { danger_level = f; return this; };
	EvadeSpellData* set_danger_level(DangerLevel v) { danger_level = [v](DetectedSpell* spell) { return v; }; return this; };

	EvadeSpellData* set_start_position		(const std::function<Vec2(DetectedSpell*)>& v)  { start_position = v; return this; }
	EvadeSpellData* set_start_position		(const Vec2& v)					  { start_position = [v](DetectedSpell*) { return v; }; return this; }

	EvadeSpellData* set_end_position		(const std::function<Vec2(DetectedSpell*)>& v)  { end_position = v; return this; }
	EvadeSpellData* set_end_position		(const Vec2& v)					  { end_position = [v](DetectedSpell*) { return v; }; return this; }

	EvadeSpellData* set_on_process_spell	(const std::function<void(SpellCastInfo*)>& fn)  { on_process_spell = fn; return this; }
	EvadeSpellData* set_on_create_object	(const std::function<void(DetectedSpell*)>& fn)  { on_create_object = fn; return this; }
	EvadeSpellData* set_on_assign_object	(const std::function<void(DetectedSpell*)>& fn)  { on_assign_object = fn; return this; }

	EvadeSpellData* set_hero_hash			(CharacterHash hash) { hero_hash = hash; return this; }
	EvadeSpellData* set_menu_name			(const char* name)	 { menu_name = name; return this; }
};