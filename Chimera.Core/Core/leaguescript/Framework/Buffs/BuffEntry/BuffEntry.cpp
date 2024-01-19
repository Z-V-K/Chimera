#include "../pch.h"
#include "BuffEntry.h"

#include "../Framework/GameEngine/GameTime/GameTime.h"
#include "../Framework/GameEngine/ObjectManager/ObjectManager.h"
#include "../Framework/Containers/RiotString.h"
#include "../Impl/Common/Utils.h"
#include "../Impl/Hooks/retspoof/x64RetSpoof.h"
#include "../Framework/Rendering/r3dTexture/r3dTexture.h"

bool BuffEntry::is_valid() const
{
	typedef bool(__fastcall* fnIsValid)(const BuffEntry*);
	static fnIsValid fn = (fnIsValid)MAKE_RVA(Addresses::BuffEntry::IsValid);
	return x64RetSpoof::spoof_call(fn, this);
}

int BuffEntry::get_count_alt() const
{
	return RVA_CAST_THIS(int32_t, Structures::BuffEntry::CountAlt);
}

int BuffEntry::get_count_int() const
{
	return RVA_CAST_THIS(int32_t, Structures::BuffEntry::CountInt);
}

float BuffEntry::get_count_float() const
{
	return RVA_CAST_THIS(float, Structures::BuffEntry::CountFloat);
}

GameObject* BuffEntry::get_caster() const
{
	if (!is_valid())
		return nullptr;

	uint64_t* addr = RVA_CAST_THIS(uint64_t*, Structures::BuffEntry::BuffCasterData);

	if (!addr)
		return nullptr;

	uint64_t* pBuffCasterData = *reinterpret_cast<uint64_t**>(addr);

	if (!pBuffCasterData)
		return nullptr;

	uint32_t* pHandle = reinterpret_cast<uint32_t*>((uintptr_t)pBuffCasterData + (uintptr_t) Structures::BuffEntry::BuffCasterDataCasterHandle);

	if (!pHandle)
		return nullptr;

	if (*pHandle == 0)
		return nullptr;

	return ObjectManager::find_object(*pHandle);
}

GameObject* BuffEntry::get_owner() const
{
	if (!is_valid())
		return nullptr;

	const uintptr_t owner_data = RVA_CAST_THIS(uintptr_t, Structures::BuffEntry::BuffOwnerData);

	if (!owner_data)
		return nullptr;

	return *(GameObject**)(owner_data + (uintptr_t)Structures::BuffEntry::BuffOwnerObject);
}

Enums::BuffType BuffEntry::get_type() const
{
	return RVA_CAST_THIS(Enums::BuffType, Structures::BuffEntry::Type);
}

float BuffEntry::get_start_time() const
{
	return RVA_CAST_THIS(float, Structures::BuffEntry::StartTime);
}

float BuffEntry::get_end_time() const
{
	return RVA_CAST_THIS(float, Structures::BuffEntry::EndTime);
}

std::string BuffEntry::get_name() const
{
	void* buffScript = RVA_CAST_THIS(void*, Structures::BuffEntry::BuffData);

	if (!buffScript)
		return "";

	char* str = *reinterpret_cast<char**>((uintptr_t)buffScript + (uintptr_t)Structures::BuffData::Name);

	if (!str || !Utils::is_valid_string(str))
		return "";

	return str;
}

uint32_t BuffEntry::get_hash() const
{
	void* buffScript = RVA_CAST_THIS(void*, Structures::BuffEntry::BuffData);

	if (!buffScript)
		return 0x0;

	return *reinterpret_cast<uint32_t*>((uintptr_t)buffScript + (uintptr_t)Structures::BuffData::Hash);
}

PVOID BuffEntry::get_texture() const
{
	void* buffScript = RVA_CAST_THIS(void*, Structures::BuffEntry::BuffData);

	if (!buffScript)
		return 0x0;

	r3dTexture* ptr = *reinterpret_cast<r3dTexture**>((uintptr_t)buffScript + (uintptr_t)Structures::BuffData::Texture);

	if (!ptr)
		return nullptr;

	return ptr->get_dx_texture();
}

int BuffEntry::get_count() const
{
	if (int buffCountInt{ this->get_count_int() }; buffCountInt != 0)
		return buffCountInt;

	if (float buffCountFloat{ this->get_count_float() }; buffCountFloat != 0)
		return static_cast<int>(buffCountFloat);

	if (int buffCountAlt{this->get_count_alt()}; buffCountAlt != 0)
		return buffCountAlt;

	return 0;
}

float BuffEntry::get_remaining_time() const
{
	float remainingTime{ get_end_time() - GameClock::get_time() };

	return remainingTime > 0.0f ? remainingTime : 0.0f;
}

float BuffEntry::get_total_duration() const
{
	return get_end_time() - get_start_time();
}

