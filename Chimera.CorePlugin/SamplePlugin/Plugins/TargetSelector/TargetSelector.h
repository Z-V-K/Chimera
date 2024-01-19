#pragma once

namespace TargetSelector
{
	enum SelectionMode
	{
		Auto,
		LowestHp,
		LowestMaxHp,
		HighestHp,
		HighestMaxHp,
		LeastSpells,
		LeastAutos,
		Closest,
		StrictPriority
	};

	namespace Menu
	{
		inline MenuTab* main_menu;
		inline MenuItem* selection_mode;
	}

	inline GameObject* forced_target = nullptr;
	
	void initialize();

	GameObject* get_target(float range, DamageType damage_type, bool ignore_invulnerability = false);
	GameObject* get_target2(const std::vector<GameObject*>& objects, DamageType damage_type);
	GameObject* get_selected_target();
	void set_selected_target(GameObject* target);
};
