#pragma once

struct PredictedDamage
{
    int start_tick;
    float projectile_speed;
    float animation_time;
    float target_bounding_radius;
    double damage;
    float delay;
    GameObject* source;
    GameObject* target;
    bool is_skillshot;
    bool processed;
};

namespace HealthPrediction
{
    void on_process_spell(SpellCastInfo* processed_spell);
    void on_cast_complete(SpellCastInfo* processed_spell);
    void on_stop_cast(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled);
    void on_delete_object(GameObject* obj);
    void on_game_update();

	float get_health_prediction(GameObject* obj, int time, int delay = 50);
	float get_incoming_damage(GameObject* obj, int time, int delay = 50);
    bool has_turret_aggro(GameObject* minion);
    bool has_minion_aggro(GameObject* minion);
    int turret_aggro_start_time(GameObject* minion);
    GameObject* get_aggro_turret(GameObject* minion);

    void initialize();
};