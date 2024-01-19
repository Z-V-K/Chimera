#pragma once

#include <rapidjson/document.h>

class ConfigManager
{
public:
	void load_config();
	void save_config();
private:
	rapidjson::Value json_root;
	rapidjson::MemoryPoolAllocator<> allocator;
};

extern ConfigManager* g_config_manager;