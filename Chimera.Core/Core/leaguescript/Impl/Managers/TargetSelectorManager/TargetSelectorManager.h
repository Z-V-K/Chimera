#pragma once
#include "../Impl/Managers/DmgLibManager/DamageLibManager.h"
#include "../Framework/GameObjects/GameObject/GameObject.h"

class TargetSelectorManager
{
private:
	typedef GameObject* (*fn_get_target)(float, DamageType, bool);
	typedef GameObject* (*fn_get_target2)(const std::vector<GameObject*>&, DamageType);
	typedef GameObject* (*fn_get_selected_target)();
	typedef void (*fn_set_selected_target)(GameObject*);

	fn_get_target _get_target = nullptr;
	fn_get_target2 _get_target2 = nullptr;
	fn_get_selected_target _get_selected_target = nullptr;
	fn_set_selected_target _set_selected_target = nullptr;
public:

	virtual void setCallbacks(
		fn_get_target get_target,
		fn_get_target2 get_target2,
		fn_get_selected_target get_selected_target,
		fn_set_selected_target set_selected_target
	);

	virtual GameObject* get_target(float range, DamageType damage_type, bool ignore_invulnerability = false);
	virtual GameObject* get_target(const std::vector<GameObject*>& objects, DamageType damage_type);
	virtual GameObject* get_selected_target();
	virtual void set_selected_target(GameObject* target);

	void remove_callbacks();
};

extern TargetSelectorManager* g_target_selector_manager;