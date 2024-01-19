#include "../pch.h"
#include "BuffManager.h"

#include "../Impl/Base/base.h"
#include "../Framework/GameEngine/GameTime/GameTime.h"

uint64_t BuffManager::get_buff_entries_array()
{
	return *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(Structures::BuffManager::BuffEntriesArray));
}

uint64_t BuffManager::get_buff_entries_array_end()
{
	return *reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(this) + static_cast<uintptr_t>(Structures::BuffManager::BuffEntriesArrayEnd));
}

bool buffFilter(BuffEntry* buff);

std::vector<BuffEntry*> BuffManager::get_buffs()
{
	std::vector<BuffEntry*> buffs{ };

	const uintptr_t buffArrayStart = get_buff_entries_array();
	const uintptr_t buffArrayEnd = get_buff_entries_array_end();
	
	if (!buffArrayStart || !buffArrayEnd)
		return buffs;

	const int size = (buffArrayEnd - buffArrayStart) >> 4;
	if (!((buffArrayEnd - buffArrayStart) >> 4)) // (end - start) > 0x16
		return buffs;

	for (size_t i = 0; i < size; i++)
	{
		auto buff = *(BuffEntry**)(buffArrayStart + 0x10 * i);

		if (!buff || !buff->is_valid())
			continue;

		buffs.push_back(buff);
	}

	return buffs;
}

std::vector<BuffEntry*> BuffManager::get_buffs(Enums::BuffType buffs_type)
{
	std::vector<BuffEntry*> buffs{  };

	for (const auto& buff : get_buffs())
	{
		if (buff->get_type() != buffs_type)
			continue;

		buffs.push_back(buff);
	}

	return buffs;
}

BuffEntry* BuffManager::get_buff(const std::string& buff_name)
{
	std::vector<BuffEntry*> buffs = get_buffs();

	for (const auto& buff : buffs)
	{
		if (!strcmp(buff_name.c_str(), buff->get_name().c_str()))
			return buff;
	}

	return nullptr;
}

BuffEntry* BuffManager::get_buff_by_hash(const uint32_t buff_hash)
{
	std::vector<BuffEntry*> buffs = get_buffs();

	for (const auto& buff : buffs)
	{
		if (buff->get_hash() == buff_hash)
			return buff;
	}

	return nullptr;
}

bool BuffManager::has_buff_type(Enums::BuffType buff_type)
{
	typedef bool(__thiscall* vtableFunc)(PVOID, uint8_t);
	return base::call_virtual<vtableFunc>(this, static_cast<uintptr_t>(Structures::BuffManagerVTable::HasBuffOfType))(this, (uint8_t)buff_type);
}

bool buffFilter(BuffEntry* buff)
{
	if (!buff || (uintptr_t)buff <= 0x1000)
		return false;

	if (static_cast<int>(buff->get_type()) == -1 || static_cast<int>(buff->get_type()) > 40)
		return false;

	if (static_cast<int>(GameClock::get_time()) > buff->get_end_time())
		return false;

	if (buff->get_hash() == 0x0 || buff->get_count_alt() == 0)
		return false;

	return true;
}