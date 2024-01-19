#pragma once

namespace TurretMissileManager
{
	void initialize();
	void on_unload();

	void on_create(GameObject* obj);
	void on_delete(GameObject* obj);
	void on_process_spell(SpellCastInfo* spell);

	GameObject* get_target();
	bool is_attack_valid();
	double get_damage();
	int get_predicted_land_time();
	GameObject* get_closest_turret();
};