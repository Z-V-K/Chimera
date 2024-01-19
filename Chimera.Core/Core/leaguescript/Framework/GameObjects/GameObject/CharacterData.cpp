#include "../pch.h"
#include "CharacterData.h"

#include "../Impl/Common/Common.h"

float BaseCharacterData::get_base_health() const
{
	return RVA_CAST_THIS(float, Structures::CharacterBaseData::BaseHealth);
}

float BaseCharacterData::get_base_mana() const
{
	return RVA_CAST_THIS(float, Structures::CharacterBaseData::BaseMana);
}

BaseCharacterData* CharacterData::get_base_character_data() const
{
	return RVA_CAST_THIS(BaseCharacterData*, Structures::CharacterData::BaseCharacterData);
}

uint32_t CharacterData::get_character_hash() const
{
	return RVA_CAST_THIS(uint32_t, Structures::CharacterData::CharacterHash);
}
