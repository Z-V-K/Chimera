#pragma once

class Texture {
public:
	static Texture* load_from_memory(unsigned char* tex, const std::string& file_name);
	static Texture* load_from_file(const std::string& file);
public:
	void* resource_view;
	uint32_t hash;
	std::string file_path;
	int width, height;
};