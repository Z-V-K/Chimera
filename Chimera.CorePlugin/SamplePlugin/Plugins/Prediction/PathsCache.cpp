#include "PathsCache.h"

std::map<GameObject*, Path> stored_paths{ };

void PathsCache::initialize()
{
    callbacks<EventType::OnSetPath>::add_callback(on_new_path, "PathsCache");
}

void PathsCache::on_unload()
{

}

Path PathsCache::get_current_path(GameObject* unit)
{
    if (!unit || !stored_paths.contains(unit))
        return Path();

    return stored_paths[unit];
}

void PathsCache::on_new_path(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed)
{
    if (sender == nullptr || !sender->is_hero())
        return;
    
    if (!stored_paths.contains(sender))
        stored_paths.insert({ sender, { } });

    Path new_path {
        path,
        game_time->get_tick_count()
    };

    stored_paths[sender] = new_path;
}