#include "../pch.h"
#include "SpellTargetClient.h"

uintptr_t SpellTargetClient::get_cast_spell_argument()
{
	return (uintptr_t) this + (uintptr_t) Structures::SpellTargetClient::CastSpellArgument;
}
int SpellTargetClient::get_caster_game_object_index()
{
	return RVA_CAST_THIS(int, Structures::SpellTargetClient::CasterGameObjectIndex);
}
int SpellTargetClient::get_target_game_object_index()
{
	return RVA_CAST_THIS(int, Structures::SpellTargetClient::TargetGameObjectIndex);
}
const Vec3& SpellTargetClient::get_spell_start_position()
{
	return RVA_CAST_THIS(Vec3, Structures::SpellTargetClient::SpellStartPosition);
}
const Vec3& SpellTargetClient::get_target_position()
{
	return RVA_CAST_THIS(Vec3, Structures::SpellTargetClient::SpellEndPosition);
}
const Vec3& SpellTargetClient::get_target_position2()
{
	return RVA_CAST_THIS(Vec3, Structures::SpellTargetClient::SpellEndPosition2);
}
const Vec3& SpellTargetClient::get_target_position3()
{
	return RVA_CAST_THIS(Vec3, Structures::SpellTargetClient::SpellEndPosition3);
}
void SpellTargetClient::set_caster_index(uint32_t index)
{
	*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::CasterGameObjectIndex)) = index;
}
void SpellTargetClient::set_target_index(uint32_t index)
{
	*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::TargetGameObjectIndex)) = index;
}
void SpellTargetClient::set_start_position(const Vec3& pos)
{
	*reinterpret_cast<Vec3*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::SpellStartPosition)) = pos;
}
void SpellTargetClient::set_target_position(const Vec3& pos)
{
	*reinterpret_cast<Vec3*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::SpellEndPosition)) = pos;
}
void SpellTargetClient::set_target_position2(const Vec3& pos)
{
	*reinterpret_cast<Vec3*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::SpellEndPosition2)) = pos;
}
void SpellTargetClient::set_target_position3(const Vec3& pos)
{
	*reinterpret_cast<Vec3*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(
		Structures::SpellTargetClient::SpellEndPosition3)) = pos;
}