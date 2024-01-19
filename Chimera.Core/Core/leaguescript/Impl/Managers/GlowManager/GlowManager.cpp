#include "GlowManager.h"

GlowManager* g_glow_manager = new GlowManager();

bool GlowManager::register_glow_object(GameObject* obj, uint32_t color, int glow_size, int glow_blur)
{
	if (!glow_objects.contains(obj))
	{
		glow_objects.insert({ obj, { } });
	}
	
	glow_objects[obj].push_back({ color, glow_size, glow_blur });
	return true;
}

bool GlowManager::remove_glow_object(GameObject* obj)
{
	if (!glow_objects.contains(obj))
		return false;

	glow_objects.erase(obj);
	return true;
}

bool GlowManager::is_glowing(GameObject* obj)
{
	return glow_objects.contains(obj);	
}