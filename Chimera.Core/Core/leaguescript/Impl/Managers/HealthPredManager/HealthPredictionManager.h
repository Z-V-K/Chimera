#pragma once

#include "../Framework/GameObjects/GameObject/GameObject.h"

class HealthPredictionManager
{
private:
	typedef float(*fn_get_health_prediction)(GameObject*, int, int);
	typedef float(*fn_get_incoming_damage)(GameObject*, int, int);
	typedef bool(*fn_has_turret_aggro)(GameObject*);
	typedef bool(*fn_has_minion_aggro)(GameObject*);
	typedef int(*fn_turret_aggro_start_time)(GameObject*);
	typedef GameObject*(*fn_get_aggro_turret)(GameObject*);

	fn_get_health_prediction get_health_prediction_ = nullptr;
	fn_get_incoming_damage get_incoming_damage_ = nullptr;
	fn_has_turret_aggro has_turret_aggro_ = nullptr;
	fn_has_minion_aggro has_minion_aggro_ = nullptr;
	fn_turret_aggro_start_time turret_aggro_start_time_ = nullptr;
	fn_get_aggro_turret get_aggro_turret_ = nullptr;
public:

	virtual void set_callbacks(
		fn_get_health_prediction get_health_prediction,
		fn_get_incoming_damage get_incoming_damage,
		fn_has_turret_aggro has_turret_aggro,
		fn_has_minion_aggro has_minion_aggro,
		fn_turret_aggro_start_time turret_aggro_start_time,
		fn_get_aggro_turret get_aggro_turret
	);

	virtual float get_health_prediction(GameObject* obj, int time, int delay = 70);
	virtual float get_incoming_damage(GameObject* obj, int time, int delay = 70);
	virtual bool has_turret_aggro(GameObject* minion);
	virtual bool has_minion_aggro(GameObject* minion);
	virtual int turret_aggro_start_time(GameObject* minion);
	virtual GameObject* get_aggro_turret(GameObject* minion);

	void remove_callbacks();
};

extern HealthPredictionManager* g_health_pred_manager;