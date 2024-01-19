#pragma once

struct Path
{
    std::vector<Vec3> path;
    int tick;

    double time()
    {
        return (game_time->get_tick_count() - tick) / 1000.0;
    }
};

class PathsCache : public Singleton<PathsCache>
{
public:
    void initialize();
    void on_unload();
    Path get_current_path(GameObject* unit);
    static void on_new_path(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed);
};
