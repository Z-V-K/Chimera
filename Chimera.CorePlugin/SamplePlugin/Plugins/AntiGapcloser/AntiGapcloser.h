#pragma once

namespace AntiGapcloser
{
	void initialize();

	GapCloserInformation get_gapcloser_information(GameObject* obj, bool all_dash = false);
	bool add_callback(gapcloser_event callback);

	void on_update();
	void on_new_path(GameObject* sender, const std::vector<Vec3>& path, bool is_dash, float dash_speed);
	void on_process_spell(SpellCastInfo* spell);
};