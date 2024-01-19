#include "../pch.h"
#include "MissileClient.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"

#include "../Framework/Containers/RiotString.h"

SpellData* MissileClient::get_spell_data() const
{
	return RVA_CAST_THIS(SpellData*, Structures::MissileClient::SpellInfo);
}

std::string MissileClient::get_caster_name() const
{
	return RVA_CAST_THIS_REF(LolString*, Structures::MissileClient::CasterName)->Get();
}

const Vec3& MissileClient::get_start_position() const
{
	return RVA_CAST_THIS(Vec3, Structures::MissileClient::StartPosition);
}

const Vec3& MissileClient::get_end_position() const
{
	return RVA_CAST_THIS(Vec3, Structures::MissileClient::EndPosition);
}

const Vec3& MissileClient::get_cast_position() const
{
	return RVA_CAST_THIS(Vec3, Structures::MissileClient::CastPosition);
}

Enums::SpellSlot MissileClient::get_slot() const
{
	return RVA_CAST_THIS(Enums::SpellSlot, Structures::MissileClient::Slot);
}

unsigned MissileClient::get_missile_index() const
{
	return RVA_CAST_THIS(unsigned, Structures::MissileClient::MissileIndex);
}

unsigned MissileClient::get_caster_index() const
{
	return RVA_CAST_THIS(unsigned, Structures::MissileClient::CasterIndex);
}

unsigned MissileClient::get_target_index() const
{
	const int array_size = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(Structures::MissileClient::TargetArraySize));

	if (array_size == 0)
		return 0;
	const uint32_t* targets_array = *reinterpret_cast<uint32_t**>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(Structures::MissileClient::TargetArray));

	return targets_array[0];
}

GameObject* MissileClient::get_source() const
{
	return ObjectManager::find_object(get_caster_index());
}

GameObject* MissileClient::get_target() const
{
	const auto index = get_target_index();
	return index != 0 ? ObjectManager::find_object(get_target_index()) : nullptr;
}