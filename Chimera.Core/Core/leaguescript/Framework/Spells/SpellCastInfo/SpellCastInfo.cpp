#include "../pch.h"
#include "SpellCastInfo.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"

unsigned SpellCastInfo::get_src_index() const
{
	return RVA_CAST_THIS(unsigned, Structures::SpellCastInfo::SrcIndex);
}
unsigned SpellCastInfo::get_target_index() const
{
	const auto targetPtr = RVA_CAST_THIS(uint32_t*, Structures::SpellCastInfo::TargetIndex);

	return targetPtr ? *targetPtr : 0;
}
SpellData* SpellCastInfo::get_spell_data() const
{
	return RVA_CAST_THIS(SpellData*, Structures::SpellCastInfo::SpellData);
}
const Vec3& SpellCastInfo::get_start_pos() const
{
	return RVA_CAST_THIS(Vec3, Structures::SpellCastInfo::StartPos);
}
const Vec3& SpellCastInfo::get_end_pos() const
{
	return RVA_CAST_THIS(Vec3, Structures::SpellCastInfo::EndPos);
}
const Vec3& SpellCastInfo::get_cast_pos() const
{
	return RVA_CAST_THIS(Vec3, Structures::SpellCastInfo::CastPos);
}
bool SpellCastInfo::is_auto() const
{
	return RVA_CAST_THIS(bool, Structures::SpellCastInfo::IsAuto);
}
bool SpellCastInfo::is_spell() const
{
	return RVA_CAST_THIS(bool, Structures::SpellCastInfo::IsSpell);
}
bool SpellCastInfo::is_special_attack() const
{
	return RVA_CAST_THIS(bool, Structures::SpellCastInfo::IsSpecialAttack);
}
Enums::SpellSlot SpellCastInfo::get_slot() const
{
	return RVA_CAST_THIS(Enums::SpellSlot, Structures::SpellCastInfo::Slot);
}
GameObject* SpellCastInfo::get_source() const
{
	return ObjectManager::get_instance()->find_object(get_src_index());
}
GameObject* SpellCastInfo::get_target() const
{
	return ObjectManager::get_instance()->find_object(get_target_index());
}

float SpellCastInfo::get_cast_delay() const
{
	return RVA_CAST_THIS(float, Structures::SpellCastInfo::CastDelay);
}
