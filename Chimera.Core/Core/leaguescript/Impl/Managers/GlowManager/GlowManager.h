#pragma once
#include "../Framework/GameObjects/GameObject/GameObject.h"

struct GlowData
{
	uint32_t color;
	int glow_size;
	int glow_blur;
};

class GlowManager final
{
public:
	std::unordered_map<GameObject*, std::vector<GlowData>> glow_objects{ };

	virtual bool register_glow_object(GameObject* obj, uint32_t color, int glow_size, int glow_blur);
	virtual bool remove_glow_object(GameObject* obj);
	virtual bool is_glowing(GameObject* obj);
};

extern GlowManager* g_glow_manager;
