#pragma once

#include "../Framework/Enums/CollisionFlag.h"
#include "../Impl/Common/Common.h"
#include "../Impl/Vector/Vector.h"

#ifndef EXPORT_FUNC
#define EXPORT_FUNC(RET, NAME, ARGS_IN, ARGS_OUT ) \
virtual RET __EXPORT##NAME ARGS_IN { return obj->NAME ARGS_OUT; };
#endif

struct cell_locator
{
	uint16_t x;
	uint16_t y;
};

class NavGrid final
{
public:
	uintptr_t* get_flag_map();
	uint32_t get_cell_count_x();
	uint32_t get_cell_count_y();

	float get_cell_height(float a1, float a2);
};

class NavMesh final
{
public:
	static NavMesh* instance();
	NavGrid* get_nav_grid();
	float get_height_for_position(const Vec3& world_pos);
	bool is_in_fow(const Vec3& world_pos);
	bool is_wall(Vec3& world_pos); // change this to use navcell flags
	Enums::CollisionFlags get_pos_flags(const Vec3& world_pos);
	uint8_t get_cell_flags(const cell_locator& cell);
	void set_pos_flags(const Vec3& world_pos, uint16_t flag);
	void set_cell_flags(const cell_locator& cell, uint16_t flag);
	cell_locator get_cell_locator(const Vec3& world_pos);
	Vec3 get_cell_center(const cell_locator& cell);
	int get_cell_count_x();
	int get_cell_count_y();

	EXPORT_FUNC(float, get_height_for_position, (NavMesh* obj, const Vec3& pos), (pos));
	EXPORT_FUNC(Enums::CollisionFlags, get_pos_flags, (NavMesh* obj, const Vec3& pos), (pos));
	EXPORT_FUNC(uint8_t, get_cell_flags, (NavMesh* obj, const cell_locator& cell), (cell));
	EXPORT_FUNC(bool, is_in_fow, (NavMesh* obj, const Vec3& pos), (pos));
	EXPORT_FUNC(void, set_pos_flags, (NavMesh* obj, const Vec3& worldPos, uint16_t flag), (worldPos, flag));
	EXPORT_FUNC(void, set_cell_flags, (NavMesh* obj, const cell_locator& cell, uint16_t flag), (cell, flag));
	EXPORT_FUNC(cell_locator, get_cell_locator, (NavMesh* obj, const Vec3& world_pos), (world_pos));
	EXPORT_FUNC(Vec3, get_cell_center, (NavMesh* obj, const cell_locator& cell), (cell));
	EXPORT_FUNC(int, get_cell_count_x, (NavMesh* obj), ());
	EXPORT_FUNC(int, get_cell_count_y, (NavMesh* obj), ());
};
#undef EXPORT_FUNC