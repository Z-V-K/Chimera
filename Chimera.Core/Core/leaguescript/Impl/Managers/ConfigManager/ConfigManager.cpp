#include "../pch.h"
#include "ConfigManager.h"

#include "../Impl/Managers/MenuManager/MenuManager.h"
#include "../Core/Context/Context.h"

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

ConfigManager* g_config_manager = new ConfigManager();

void ConfigManager::load_config()
{
	std::ifstream fstream{ g_ctx->config_path.c_str() };
	if (!fstream.good())
	{
		// create empty json
		std::ofstream ofstream{ g_ctx->config_path.c_str() };
		ofstream << "{ }";
		ofstream.close();

		fstream.close();
		return;
	}
	fstream.close();

	FILE* fp = fopen(g_ctx->config_path.c_str(), "rb");

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document root;
	if (root.ParseStream(is).HasParseError())
	{
		// re-create a valid json file
		std::ofstream out(g_ctx->config_path.c_str(), std::ios::trunc);
		out << "{ }";
		out.close();
		fstream.close();
		fclose(fp);
		return;
	}

	json_root = root.GetObj();
	allocator = root.GetAllocator();

	for (const auto& menu : MenuManager::get_menus())
	{
		if (!json_root.HasMember(menu->get_key().c_str()))
		{
			rapidjson::Value key(menu->get_key().c_str(), allocator);
			rapidjson::Value val(rapidjson::Value(rapidjson::kObjectType), allocator);
			json_root.AddMember(key, val, allocator);
		}

		menu->init_from_config(json_root[menu->get_key().c_str()], allocator);
	}

	fp = fopen(g_ctx->config_path.c_str(), "wb");

	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::Writer writer(os);
	json_root.Accept(writer);

	fclose(fp);
	fstream.close();
}

void ConfigManager::save_config()
{
	if (json_root.IsNull())
	{
		load_config();
		save_config();
		return;
	}

	bool hasConfigChanged = false;

	for (const auto& menu : MenuManager::get_menus())
	{
		if (!json_root.HasMember(menu->get_key().c_str()))
		{
			rapidjson::Value key(menu->get_key().c_str(), allocator);
			rapidjson::Value val(rapidjson::Value(rapidjson::kObjectType), allocator);
			json_root.AddMember(key, val, allocator);
		}

		if (menu->update_config(json_root[menu->get_key().c_str()], allocator))
			hasConfigChanged = true;
	}

	if (hasConfigChanged)
	{
		FILE* fp = fopen(g_ctx->config_path.c_str(), "wb");

		char writeBuffer[65536];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		json_root.Accept(writer);

		fclose(fp);
	}
}