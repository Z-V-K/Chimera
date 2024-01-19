#include "../pch.h"
#include "TargetSelectorManager.h"

TargetSelectorManager* g_target_selector_manager = new TargetSelectorManager();

GameObject* TargetSelectorManager::get_target(float range, DamageType damage_type, bool ignore_invulnerability)
{
	if (_get_target)
		return _get_target(range, damage_type, ignore_invulnerability);

	return nullptr;
}

GameObject* TargetSelectorManager::get_target(const std::vector<GameObject*>& objects, DamageType damage_type)
{
	if (_get_target2)
		return _get_target2(objects, damage_type);

	return nullptr;
}

GameObject* TargetSelectorManager::get_selected_target()
{
	if (_get_selected_target)
		return _get_selected_target();

	return nullptr;
}

void TargetSelectorManager::set_selected_target(GameObject* target)
{
	if (_set_selected_target)
		_set_selected_target(target);
}

void TargetSelectorManager::setCallbacks(
	fn_get_target get_target,
	fn_get_target2 get_target2,
	fn_get_selected_target get_selected_target,
	fn_set_selected_target set_selected_target)
{
	_get_target = get_target;
	_get_target2 = get_target2;
	_get_selected_target = get_selected_target;
	_set_selected_target = set_selected_target;
}

void TargetSelectorManager::remove_callbacks()
{
	_get_target = nullptr;
	_get_target2 = nullptr;
	_get_selected_target = nullptr;
	_set_selected_target = nullptr;
}
