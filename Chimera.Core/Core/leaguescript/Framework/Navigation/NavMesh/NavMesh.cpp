#include "../pch.h"
#include "NavMesh.h"

#include "../Impl/Base/base.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"

NavMesh* NavMesh::instance()
{
	return RVA_CAST(NavMesh*, Addresses::NavMesh::NavMeshInstance);
}

NavGrid* NavMesh::get_nav_grid()
{
	return RVA_CAST_THIS(NavGrid*, Structures::NavMesh::NavGrid);
}

uintptr_t* NavGrid::get_flag_map()
{
	return RVA_CAST_THIS(uintptr_t*, Structures::NavGrid::FlagsMap);
}

uint32_t NavGrid::get_cell_count_x()
{
	return RVA_CAST_THIS(uint32_t, Structures::NavGrid::CellCountX);
}

uint32_t NavGrid::get_cell_count_y()
{
	return RVA_CAST_THIS(uint32_t, Structures::NavGrid::CellCountY);
}

float NavGrid::get_cell_height(float a1, float a2)
{
	typedef float(__fastcall* fnGetHeight)(float, float);
	static fnGetHeight fn = (fnGetHeight)MAKE_RVA(Addresses::NavMesh::GetCellHeight);

	return x64RetSpoof::spoof_call(fn, a1, a2);
}

float NavMesh::get_height_for_position(const Vec3& world_pos)
{
	return get_nav_grid()->get_cell_height(world_pos.x, world_pos.z);
}

bool NavMesh::is_in_fow(const Vec3& worldPos)
{
	typedef bool(__fastcall* fnIsInFOW)(const Vec3*);
	static fnIsInFOW fn = (fnIsInFOW)MAKE_RVA(Addresses::NavMesh::IsInFOW);

	return x64RetSpoof::spoof_call(fn, &worldPos);
}

bool NavMesh::is_wall(Vec3& world_pos)
{
	typedef bool(__fastcall* fnIsNotWall)(Vec3*, int);
	static fnIsNotWall fn = (fnIsNotWall)MAKE_RVA(Addresses::NavMesh::IsNotWall);

	return !x64RetSpoof::spoof_call(fn, &world_pos, 1);
}

Enums::CollisionFlags NavMesh::get_pos_flags(const Vec3& world_pos)
{
	typedef DWORD(__fastcall* fnGetCellFlags)(const Vec3*);
	static fnGetCellFlags fn = (fnGetCellFlags)MAKE_RVA(Addresses::NavMesh::GetCellFlags);

	return (Enums::CollisionFlags) x64RetSpoof::spoof_call(fn, &world_pos);
}

uint8_t NavMesh::get_cell_flags(const cell_locator& cell)
{
	int64_t cellFlagStructSize = 0x10;
	int64_t flagOffset = 0x8;

	NavGrid* navgrid = get_nav_grid();
	auto p = (uint64_t*)((uintptr_t)navgrid->get_flag_map() + cellFlagStructSize * (cell.x + cell.y * navgrid->get_cell_count_x()));

	return *((uint8_t*)((uintptr_t)p + flagOffset));
}

void NavMesh::set_pos_flags(const Vec3& world_pos, uint16_t flag)
{
	cell_locator locator = get_cell_locator(world_pos);

	set_cell_flags(locator, flag);
}

void NavMesh::set_cell_flags(const cell_locator& cell, uint16_t flag)
{
	int64_t cellFlagStructSize = 0x10;
	int64_t flagOffset = 0x8;

	NavGrid* navgrid = get_nav_grid();
	auto p = (uint64_t*)((uintptr_t)navgrid->get_flag_map() + cellFlagStructSize * (cell.x + cell.y * navgrid->get_cell_count_x()));

	*((uint8_t*)((uintptr_t)p + flagOffset)) = flag;
}

cell_locator NavMesh::get_cell_locator(const Vec3& world_pos)
{
	typedef int64_t(__fastcall* fnGetCellLocator)(cell_locator*, const Vec3*);
	static fnGetCellLocator fn = (fnGetCellLocator)(MAKE_RVA(Addresses::NavMesh::GetCellLocator));
	cell_locator locator;
	x64RetSpoof::spoof_call(fn, &locator, &world_pos);

	return locator;
}

Vec3 NavMesh::get_cell_center(const cell_locator& cell)
{
	typedef Vec3*(__fastcall* fnGetcellCenter)(char*, const cell_locator* cell_locator);
	static fnGetcellCenter fn = (fnGetcellCenter)(MAKE_RVA(Addresses::NavMesh::GetCellCenter));

	char a1[16];
	return *x64RetSpoof::spoof_call(fn, a1, &cell);
}

int NavMesh::get_cell_count_x()
{
	return get_nav_grid()->get_cell_count_x();
}

int NavMesh::get_cell_count_y()
{
	return get_nav_grid()->get_cell_count_y();
}