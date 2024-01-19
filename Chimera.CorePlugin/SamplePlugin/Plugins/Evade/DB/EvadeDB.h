#pragma once
#include "EvadeSpellData.h"

namespace EvadeDB
{
	inline std::vector<EvadeSpellData*> base_database { };

	inline std::vector<EvadeSpellData*> database { };

	void initialize();
	void on_unload();

	EvadeSpellData* get_data(const uint32_t spell_hash);
	EvadeSpellData* get_data(const std::string& obj_name);
}
