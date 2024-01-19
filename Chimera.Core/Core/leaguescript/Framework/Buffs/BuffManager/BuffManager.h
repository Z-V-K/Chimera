#pragma once

#include "../Impl/Common/Common.h"
#include "../BuffEntry/BuffEntry.h"

class BuffManager final
{
public:
	uint64_t get_buff_entries_array();
	uint64_t get_buff_entries_array_end();

	std::vector<BuffEntry*> get_buffs();
	std::vector<BuffEntry*> get_buffs(Enums::BuffType buffs_type);

	BuffEntry*				get_buff(const std::string& buff_name);
	BuffEntry*				get_buff_by_hash(const uint32_t buff_hash);
	bool					has_buff_type(Enums::BuffType buff_type);
};

