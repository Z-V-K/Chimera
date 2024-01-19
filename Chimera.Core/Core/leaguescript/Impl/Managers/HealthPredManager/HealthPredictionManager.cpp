#include "HealthPredictionManager.h"

HealthPredictionManager* g_health_pred_manager = new HealthPredictionManager();

void HealthPredictionManager::set_callbacks(
	fn_get_health_prediction get_health_prediction,
	fn_get_incoming_damage get_incoming_damage,
	fn_has_turret_aggro has_turret_aggro,
	fn_has_minion_aggro has_minion_aggro,
	fn_turret_aggro_start_time turret_aggro_start_time,
	fn_get_aggro_turret get_aggro_turret)
{
	get_health_prediction_ = get_health_prediction;
	get_incoming_damage_ = get_incoming_damage;
	has_turret_aggro_ = has_turret_aggro;
	has_minion_aggro_ = has_minion_aggro;
	turret_aggro_start_time_ = turret_aggro_start_time;
	get_aggro_turret_ = get_aggro_turret;
}

float HealthPredictionManager::get_incoming_damage(GameObject* obj, int time, int delay)
{
	if (get_incoming_damage_)
		return get_incoming_damage_(obj, time, delay);

	return 0.f;
}

float HealthPredictionManager::get_health_prediction(GameObject* obj, int time, int delay)
{
	if (get_health_prediction_)
		return get_health_prediction_(obj, time, delay);

	return 0.f;
}

bool HealthPredictionManager::has_turret_aggro(GameObject* minion)
{
	if (has_turret_aggro_)
		return has_turret_aggro_(minion);

	return false;
}

bool HealthPredictionManager::has_minion_aggro(GameObject* minion)
{
	if (has_minion_aggro_)
		return has_minion_aggro_(minion);

	return false;
}

int HealthPredictionManager::turret_aggro_start_time(GameObject* minion)
{
	if (turret_aggro_start_time_)
		return turret_aggro_start_time_(minion);

	return 0;
}

GameObject* HealthPredictionManager::get_aggro_turret(GameObject* minion)
{
	if (get_aggro_turret_)
		return get_aggro_turret_(minion);

	return nullptr;
}

void HealthPredictionManager::remove_callbacks()
{
	get_health_prediction_ = nullptr;
	get_incoming_damage_ = nullptr;
	has_turret_aggro_ = nullptr;
	has_minion_aggro_ = nullptr;
	turret_aggro_start_time_ = nullptr;
	get_aggro_turret_ = nullptr;
}