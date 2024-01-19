#include "../pch.h"
#include "TextureManager.h"

#include "../Impl/DirectX/DirectX.h"
#include "../Impl/Logger/Logger.h"
#include "../Impl/UI/Texture/Texture.h"
#include "../Framework/Hash/LeagueHash.h"

const auto IMG_FOLDER = g_ctx->images_path.c_str();

void TextureManager::do_folder(const std::filesystem::directory_entry& folder)
{
	for (const auto& entry : std::filesystem::directory_iterator(folder))
	{
		if (entry.is_directory())
		{
			do_folder(entry);
			continue;
		}

		if (const Texture* image = Texture::load_from_file(entry.path().string().c_str()))
			texture_list.push_back(image);
	}
}

void TextureManager::load_textures()
{
	DWORD dwAttrib = GetFileAttributesA(IMG_FOLDER);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		return;

	for (const auto& entry : std::filesystem::directory_iterator(IMG_FOLDER))
	{
		if (entry.is_directory())
		{
			do_folder(entry);
		}
	}
}

std::uint32_t TextureManager::get_texture_hash_champion(std::string champion_name)
{
	std::string path = std::string(IMG_FOLDER) + "Champions\\" + champion_name + ".png";

	return league_hash(path.c_str());
}

std::uint32_t TextureManager::get_texture_hash_spell(std::string spell_name)
{
	std::string path = std::string(IMG_FOLDER) + "Spells\\" + spell_name + ".png";
	return league_hash(path.c_str());
}
