#include "../pch.h"
#include "Cursor.h"

#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"

const Vec3& Cursor::get_world_position()
{
	return RVA_CAST_THIS(Vec3, Structures::Cursor::Position);
}

const Vec3& Cursor::get_last_click_position()
{
	return RVA_CAST_THIS(Vec3, Structures::Cursor::LastClickPosition);
}

GameObject* Cursor::get_hovered_unit()
{
	return ObjectManager::find_object(get_hovered_unit_id());
}

unsigned Cursor::get_hovered_unit_id()
{
	return RVA_CAST_THIS(unsigned, Structures::Cursor::HoveredUnitId);
}