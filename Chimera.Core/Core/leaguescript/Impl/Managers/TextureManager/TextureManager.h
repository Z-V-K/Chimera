#pragma once

#include "../Impl/Singleton/Singleton.h"

class Texture;

class TextureManager : public singleton<TextureManager>
{
	void do_folder(const std::filesystem::directory_entry& folder);
public:
	std::vector<const Texture*> texture_list{ };
	void load_textures();

	std::uint32_t get_texture_hash_champion(std::string champion_name);
	std::uint32_t get_texture_hash_spell(std::string spell_name);
};