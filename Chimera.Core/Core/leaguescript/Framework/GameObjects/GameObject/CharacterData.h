#pragma once

class BaseCharacterData final
{
public:
	float get_base_health() const;
	float get_base_mana() const;
};

class CharacterData final
{
public:
	BaseCharacterData* get_base_character_data() const;
	uint32_t get_character_hash() const;
};