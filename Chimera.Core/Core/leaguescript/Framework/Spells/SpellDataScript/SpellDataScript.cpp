#include "../pch.h"
#include "SpellDataScript.h"

const std::string& SpellDataScript::get_name()
{
	return *RVA_CAST_THIS(std::string*, Structures::SpellDataScript::Name);
}

uint32_t SpellDataScript::get_hash()
{
	return RVA_CAST_THIS(uint32_t, Structures::SpellDataScript::Hash);
}